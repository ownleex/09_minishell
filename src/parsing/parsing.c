/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:16:06 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/13 17:29:12 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator(int character, int space)
{
	if (character == 34 || character == 39)
		return (1);
	if (character == 32 && space)
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
	else
	{
		while (line[index] != line[cursor] && line[index] != '\0')
			index++;
		if (line[index] != '\0')
			index++;
		return (index);
	}
}

int	count_args(char *line)
{
	int	len;
	int	index;

	len = 1;
	index = 0;
	while (line[index] != '\0')
	{
		if (is_separator(line[index], 1))
		{
			if (line[index] == ' ')
				len++;
			index = jump_arg(line, index);
		}
		else
			index++;
	}
	return (len);
}

int	get_arglen(t_minishell *shell, int start, int end)
{
	int	len;
	int	index;
	int	cursor;

	len = 0;
	index = start;
	cursor = 0;
	while (index <= end && shell->current_line[index])
	{
		if (is_separator(shell->current_line[index], 0))
		{
			cursor = index + 1;
			while (shell->current_line[cursor] && shell->current_line[cursor] != shell->current_line[index])
			{
				len++;
				cursor++;
			}
			index = cursor;
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

	cursor = 0;
	index = start;
	while (index <= end && src[index] != '\0')
		dest[cursor++] = src[index++];
	dest[cursor] = '\0';
}

char	*remove_outer_quotes(t_minishell *shell, int start, int end)
{
	char	*str;
	int		new_start = start;
	int		new_end = end;

	if (is_separator(shell->current_line[start], 0) &&
		shell->current_line[start] == shell->current_line[end])
	{
		new_start++;
		new_end--;
	}
	str = (char *)malloc(sizeof(char) * (new_end - new_start + 2));
	if (!str)
		return (NULL);

	copy_inner_content(str, shell->current_line, new_start, new_end);
	return (str);
}


void	set_arg(t_minishell *shell, int start, int end, int pos)
{
	shell->current_arg[pos] = remove_outer_quotes(shell, start, end);
}

int	jump_quote(t_minishell *shell, int cursor)
{
	int	index;

	index = cursor + 1;
	while (shell->current_line[index] && shell->current_line[index] != shell->current_line[cursor])
		index++;
	return (index);
}

void	**set_arguments(t_minishell *shell)
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
			set_arg(shell, old_index, index - 1, len);
			index = jump_arg(shell->current_line, index);
			old_index = index;
			len++;
		}
		if (is_separator(shell->current_line[index], 0))
			index = jump_quote(shell, index);
		index++;
	}
	set_arg(shell, old_index, index - 1, len);
	shell->current_arg[len + 1] = NULL;
	//printf("ee: %d\n", len);
	return (NULL);
}

void	parse_command(t_minishell *shell)
{
	int	len;
	char	**arguments;

	len = count_args(shell->current_line);
	arguments = (char **)malloc(sizeof(char *) * (len + 1));

	//printf("lenght: %d\n", len);
	shell->current_arg = arguments;
	set_arguments(shell);
	//printf("test: %s\n", shell->current_arg[1]);
	shell->current_cmd = shell->current_arg[0];
}
