/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:16:06 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/06 17:27:09 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator(int character)
{
	if (character == 34 || character == 39)
		return (1);
	return (0);
}

int	count_len(char *line)
{
	int	len;
	int	index;

	len = 0;
	index = 0;
	while (line[index])
	{
		if (line[index] == ' ')
			index++;
		else
		{
			len++;
			while (line[index] && line[index] != ' ')
				index++;
		}
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
	while (shell->current_line[index] && index <= end)
	{
		if (is_separator(shell->current_line[index]))
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

int	set_cmd(t_minishell *shell, char **arguments)
{
	int	len;
	int	index;

	len = 0;
	index = 0;
	while (shell->current_line[len] != ' ' && shell->current_line[len])
		len++;
	arguments[0] = (char *)malloc(sizeof(char) * (len + 1));
	while (shell->current_line[index] != ' ' && shell->current_line[index])
	{
		arguments[0][index] = shell->current_line[index];
		index++;
	}
	arguments[0][index] = '\0';
	return (len);
}

void	set_arg(t_minishell *shell, int start, int end, int pos, char **arguments)
{
	int		len;
	int		index;
	int		arg_index;
	char	quote;

	arg_index = 0;
	index = start;
	len = get_arglen(shell, start, end);
	arguments[pos] = (char *)malloc(sizeof(char) * (len + 1));
	while (shell->current_line[index] && index <= end)
	{
		if (is_separator(shell->current_line[index]))
		{
			quote = shell->current_line[index];
			index++;
			while (shell->current_line[index] && shell->current_line[index] != quote)
				arguments[pos][arg_index++] = shell->current_line[index++];
			if (shell->current_line[index] == quote)
				index++;
		}
		else
			arguments[pos][arg_index++] = shell->current_line[index++];
	}
	arguments[pos][arg_index] = '\0';
}

char	**set_arguments(t_minishell *shell, int arg_len)
{
	int	len;
	int	index;
	int	cursor;
	char	**arguments;

	len = 0;
	arguments = (char **)malloc(sizeof(char *) * (arg_len + 1));
	index = set_cmd(shell, arguments);
	while (shell->current_line[index])
	{
		if (shell->current_line[index] == ' ')
			index++;
		else
		{
			len++;
			cursor = index;
			while (shell->current_line[index] && shell->current_line[index] != ' ')
				index++;
			set_arg(shell, cursor, index - 1, len, arguments);
		}
	}
	arguments[len + 1] = NULL;
	return (arguments);
}

void	parse_command(t_minishell *shell)
{
	shell->current_arg = set_arguments(shell, count_len(shell->current_line));
	shell->current_cmd = shell->current_arg[0];
}
