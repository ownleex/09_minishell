/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:16:06 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/06 15:13:17 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	jump_quote(t_shell *shell, int cursor)
{
	int		index;
	char	quote_type;

	index = cursor + 1;
	quote_type = shell->current_line[cursor];
	while (shell->current_line[index] && \
	shell->current_line[index] != quote_type)
		index++;
	return (index);
}

void	process_argument(t_shell *shell, int *index, int *old_index, int *len)
{
	if (*index > *old_index)
		set_arg(shell, *old_index, *index - 1, (*len)++);
	*index = jump_arg(shell->current_line, *index);
	*old_index = *index;
}

void	process_pipe(t_shell *shell, int *index, int *old_index, int *len)
{
	if (*index > *old_index)
		set_arg(shell, *old_index, *index - 1, (*len)++);
	set_arg(shell, *index, *index, (*len)++);
	(*index)++;
	*old_index = *index;
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
			process_argument(shell, &index, &old_index, &len);
		else if (is_quote(shell->current_line[index]))
			index = jump_quote(shell, index);
		else if (shell->current_line[index] == '|' && \
		is_single_pipe(shell->current_line, index))
			process_pipe(shell, &index, &old_index, &len);
		else if ((shell->current_line[index] == '<' || shell->current_line[index] == '>') && \
		is_single_redirection(shell->current_line, index))
			process_pipe(shell, &index, &old_index, &len);
		else
			index++;
	}
	if (index > old_index)
		set_arg(shell, old_index, index - 1, len++);
	shell->current_arg[len] = NULL;
}

void	parse_command(t_shell *shell)
{
	int		len;
	char	**arguments;

	len = count_args(shell->current_line);
	arguments = (char **)malloc(sizeof(char *) * (len + 2));
	shell->current_arg = arguments;
	set_arguments(shell);
	handle_cmd(shell);
	print_shell_instance(shell);
	shell->current_cmd = shell->current_arg[0];
}
