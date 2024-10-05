/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instances.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:55:57 by noldiane          #+#    #+#             */
/*   Updated: 2024/10/02 02:32:08 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_arguments(t_shell *shell, t_shell *instance, int start, int end)
{
	int	i;
	int	d;

	i = start + 1;
	d = 0;
	while (i < end && shell->current_arg[i])
	{
		instance->current_arg[d] = ft_strdup(shell->current_arg[i]);
		instance->has_single_quote[d] = shell->has_single_quote[i];
		instance->was_quoted[d] = shell->was_quoted[i];
		i++;
		d++;
	}
	instance->current_arg[d] = NULL;
	instance->has_single_quote[d] = 0;
	instance->was_quoted[d] = 0;
}

void	complete_instance(t_shell *shell, t_shell *instance, int start, int end)
{
	int	arg_count;

	arg_count = end - start - 1;
	allocate_instance(instance, arg_count);
	copy_arguments(shell, instance, start, end);
	instance->current_cmd = instance->current_arg[0];
}

void	handle_pipes(t_shell *shell, int *i, t_shell **main_shell, int *c)
{
	(*main_shell)->next = malloc(sizeof(t_shell));
	if (!(*main_shell)->next)
		return ;
	ft_init((*main_shell)->next);
	complete_instance(shell, (*main_shell)->next, *i, find_end(shell, *i));
	(*main_shell)->is_piped = 1;
	*main_shell = (*main_shell)->next;
	(*c)++;
}

void	handle_redirections(t_shell *shell, int i, t_shell *main_shell)
{
	if (shell->current_arg[i][0] == '<')
		handle_input_redirection(shell, i, main_shell);
	else if (shell->current_arg[i][0] == '>')
		handle_output_redirection(shell, i, main_shell);
}

void	handle_cmd(t_shell *shell)
{
	int		i;
	int		c;
	t_shell	*main_shell;

	i = 0;
	c = 1;
	main_shell = shell;
	while (shell->current_arg[i])
	{
		if (shell->current_arg[i][0] == '|' && shell->current_arg[i + 1] \
		&& shell->was_quoted[i] == 0)
		{
			handle_pipes(shell, &i, &main_shell, &c);
			i++;
		}
		else if (is_redirecion(shell->current_arg[i]) \
		&& shell->current_arg[i + 1] && shell->was_quoted[i] == 0)
		{
			handle_redirections(shell, i, main_shell);
			i += 2;
		}
		else
			i++;
	}
	free_main_shell(shell);
}
