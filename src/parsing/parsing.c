/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:16:06 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/13 00:10:53 by ayarmaya         ###   ########.fr       */
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
	if (shell->current_line[index] == quote_type)
        return index + 1;
	return (index);
}

void process_redirection(t_shell *shell, int *index, int *old_index, int *len)
{
	if (*index > *old_index)
		set_arg(shell, *old_index, *index - 1, (*len)++);
	if (shell->current_line[*index] == '>' && shell->current_line[*index + 1] == '>')
	{
		set_arg(shell, *index, *index + 1, (*len)++);
		shell->append_output = 1;
		(*index) += 2;
	}
	else if (shell->current_line[*index] == '<' && shell->current_line[*index + 1] == '<')
	{
		set_arg(shell, *index, *index + 1, (*len)++);
		shell->is_heredoc = 1;
		(*index) += 2;
	}
	else if (shell->current_line[*index] == '>' || shell->current_line[*index] == '<')
	{
		set_arg(shell, *index, *index, (*len)++);
		(*index)++;
	}
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

void	process_argument(t_shell *shell, int *index, int *old_index, int *len)
{
	if (*index > *old_index)
		set_arg(shell, *old_index, *index - 1, (*len)++);
	*index = jump_arg(shell->current_line, *index);
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
		else if ((shell->current_line[index] == '<' || shell->current_line[index] == '>') && is_single_redirection(shell->current_line, index))
			process_redirection(shell, &index, &old_index, &len);
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
	shell->current_cmd = shell->current_arg[0];
}
