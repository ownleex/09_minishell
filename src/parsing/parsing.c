/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:16:06 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/18 17:36:19 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(int c)
{
	return (c == '"' || c == '\'');
}

int	is_redirection(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && i < 3)
	{
		if (str[i] != '>' && str[i] != '<')
			return (0);
		i++;
	}
	if (i == 2 && str[0] != str[1])
		return (0);
	return (1);
}

int	is_separator(int character, int space)
{
	if (is_quote(character))
		return (1);
	if (character == ' ' && space)
		return (1);
	return (0);
}

int	jump_arg(char *line, int cursor)
{
	int	index;

	index = cursor + 1;
	if (line[cursor] == ' ')
	{
		while (line[index] == ' ' && line[index] != '\0')
			index++;
		return (index);
	}
	else if (is_quote(line[cursor]))
	{
		index = cursor + 1;
		while (line[index] != line[cursor] && line[index] != '\0')
			index++;
		if (line[index] != '\0')
			index++;
		return (index);
	}
	else
	{
		while (line[index] != ' ' && line[index] != '\0' && \
			!is_quote(line[index]))
			index++;
		return (index);
	}
}

int	count_args(char *line)
{
	int	len;
	int	index;

	len = 0;
	index = 0;
	while (line[index] != '\0')
	{
		if (is_separator(line[index], 1))
		{
			index = jump_arg(line, index);
			len++;
		}
		else
			index++;
	}
	return (len);
}

int	get_arglen(t_shell *shell, int start, int end)
{
	int		len;
	int		index;
	char	quote_type;

	len = 0;
	index = start;
	while (index <= end && shell->current_line[index])
	{
		if (is_quote(shell->current_line[index]))
		{
			quote_type = shell->current_line[index++];
			while (shell->current_line[index] && shell->current_line[index] != quote_type)
			{
				len++;
				index++;
			}
		}
		else
			len++;
		index++;
	}
	return (len);
}

void	copy_inner_content(char *dest, char *src, int start, int end)
{
	int		index;
	int		cursor;
	char	quote_type;

	index = start;
	cursor = 0;
	while (index <= end && src[index] != '\0')
	{
		if (is_quote(src[index]))
		{
			quote_type = src[index++];
			while (index <= end && src[index] != quote_type)
				dest[cursor++] = src[index++];
		}
		else
			dest[cursor++] = src[index];
		index++;
	}
	dest[cursor] = '\0';
}

char	*remove_outer_quotes(t_shell *shell, int start, int end)
{
	char	*str;
	int		arg_len;

	arg_len = get_arglen(shell, start, end);
	str = (char *)malloc(sizeof(char) * (arg_len + 1));
	if (!str)
		return (NULL);
	copy_inner_content(str, shell->current_line, start, end);
	return (str);
}

void	set_arg(t_shell *shell, int start, int end, int pos)
{
	shell->current_arg[pos] = remove_outer_quotes(shell, start, end);
}

int	jump_quote(t_shell *shell, int cursor)
{
	int		index;
	char	quote_type;

	index = cursor + 1;
	quote_type = shell->current_line[cursor];
	while (shell->current_line[index] && shell->current_line[index] != quote_type)
		index++;
	return (index);
}

void	set_arguments(t_shell *shell)
{
	int	len;
	int	index;
	int	old_index;

	len = 0;
	index = 0;
	old_index = 0;
	while (shell->current_line[index] != '\0')
	{
		if (shell->current_line[index] == ' ')
		{
			if (index > old_index)
				set_arg(shell, old_index, index - 1, len++);
			index = jump_arg(shell->current_line, index);
			old_index = index;
		}
		else if (is_quote(shell->current_line[index]))
			index = jump_quote(shell, index);
		else
			index++;
	}
	if (index > old_index)
		set_arg(shell, old_index, index - 1, len++);
	shell->current_arg[len] = NULL;
}

void	look_redirection(t_shell *shell)
{
	int	i;

	if (!shell || !shell->current_arg)
		return ;
	i = 0;
	while (shell->current_arg[i])
	{
		if (shell->current_arg[i] != NULL && is_redirection(shell->current_arg[i]))
		{
			if (ft_strlen(shell->current_arg[i]) == 2)
				shell->append_output = 1;
			else
				shell->append_output = 0;
			if (shell->current_arg[i][0] == '<')
			{
				shell->output_file = NULL;
				shell->input_file = (char *)malloc(sizeof(char) * (ft_strlen(shell->current_arg[i + 1]) + 1));
				ft_strlcpy(shell->input_file, shell->current_arg[i + 1], ft_strlen(shell->current_arg[i + 1]) + 1);
			}
			else if (shell->current_arg[i][0] == '>')
			{
				shell->input_file = NULL;
				shell->output_file = (char *)malloc(sizeof(char) * (ft_strlen(shell->current_arg[i + 1]) + 1));
				ft_strlcpy(shell->output_file, shell->current_arg[i + 1], ft_strlen(shell->current_arg[i + 1]) + 1);
			}
			break;
		}
		i++;
	}
}

void	parse_command(t_shell *shell)
{
	int		len;
	char	**arguments;

	len = count_args(shell->current_line);
	arguments = (char **)malloc(sizeof(char *) * (len + 2));
	shell->current_arg = arguments;
	set_arguments(shell);
	look_redirection(shell);
	shell->current_cmd = shell->current_arg[0];
}
