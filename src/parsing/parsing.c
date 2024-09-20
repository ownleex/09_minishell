/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:16:06 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/19 15:13:32 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_redirection(t_shell *s, int *i, int *o_i, int *l)
{
	if (*i > *o_i)
		set_arg(s, *o_i, *i - 1, (*l)++);
	if (s->current_line[*i] == '>' && s->current_line[*i + 1] == '>')
	{
		set_arg(s, *i, *i + 1, (*l)++);
		s->append_output = 1;
		(*i) += 2;
	}
	else if (s->current_line[*i] == '<' && s->current_line[*i + 1] == '<')
	{
		set_arg(s, *i, *i + 1, (*l)++);
		s->is_heredoc = 1;
		(*i) += 2;
	}
	else if (s->current_line[*i] == '>' || s->current_line[*i] == '<')
	{
		set_arg(s, *i, *i, (*l)++);
		(*i)++;
	}
	*o_i = *i;
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

void	set_arguments(t_shell *s)
{
	int	len;
	int	i;
	int	old_index;

	len = 0;
	i = 0;
	old_index = 0;
	while (s->current_line[i] != '\0')
	{
		if (s->current_line[i] == ' ')
			process_argument(s, &i, &old_index, &len);
		else if (is_quote(s->current_line[i]))
			i = jump_quote(s, i);
		else if (s->current_line[i] == '|' && \
		is_single_pipe(s->current_line, i))
			process_pipe(s, &i, &old_index, &len);
		else if ((s->current_line[i] == '<' || s->current_line[i] == '>') \
		&& is_single_redirection(s->current_line, i))
			process_redirection(s, &i, &old_index, &len);
		else
			i++;
	}
	if (i > old_index)
		set_arg(s, old_index, i - 1, len++);
	s->current_arg[len] = NULL;
}

void	parse_command(t_shell *shell)
{
	int		len;
	char	**arguments;

	len = count_args(shell->current_line);
	arguments = (char **)malloc(sizeof(char *) * (len + 2));
	shell->current_arg = arguments;
	shell->has_single_quote = malloc(sizeof(int) * (len + 2));
	shell->was_quoted = malloc(sizeof(int) * (len + 2));
	if (!shell->has_single_quote || !shell->was_quoted)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	set_arguments(shell);
	handle_cmd(shell);
	shell->current_cmd = shell->current_arg[0];
}
