/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:03:36 by noldiane          #+#    #+#             */
/*   Updated: 2024/09/20 15:40:48 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	do_input_redirection(char *line, int index, int *len)
{
	index++;
	(*len) += 2;
	if (line[index] == '<')
		index++;
	return (index);
}

int	count_args(char *line)
{
	int	len;
	int	index;

	len = 0;
	index = 0;
	if (!line)
		return (0);
	while (line[index] != '\0')
	{
		if (is_separator(line[index], 1))
			index = do_separator(line, index, &len);
		else if (line[index] == '|' && is_single_pipe(line, index))
			index = do_pipe(index, &len);
		else if (line[index] == '>')
			index = do_redirection(line, index, &len);
		else if (line[index] == '<')
			index = do_input_redirection(line, index, &len);
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
			while (shell->current_line[index] && \
			shell->current_line[index] != quote_type)
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

void	set_arg(t_shell *shell, int start, int end, int pos)
{
	char	*str;
	int		arg_len;

	arg_len = get_arglen(shell, start, end);
	str = (char *)malloc(sizeof(char) * (arg_len + 1));
	if (!str)
		return ;
	if (is_quote(shell->current_line[start]))
	{
		shell->was_quoted[pos] = 1;
		if (shell->current_line[start] == '\'')
			shell->has_single_quote[pos] = 1;
		else
			shell->has_single_quote[pos] = 0;
	}
	else
	{
		shell->was_quoted[pos] = 0;
		shell->has_single_quote[pos] = 0;
	}
	copy_inner_content(str, shell->current_line, start, end);
	shell->current_arg[pos] = str;
}
