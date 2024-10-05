/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:15:07 by noldiane          #+#    #+#             */
/*   Updated: 2024/10/02 16:43:30 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_end(t_shell *shell, int start)
{
	int	i;

	i = start + 1;
	while (shell->current_arg[i])
	{
		if (shell->current_arg[i][0] == '|' || \
		is_redirecion(shell->current_arg[i]))
			break ;
		i++;
	}
	return (i);
}

void	reset_shell_state(t_shell *shell)
{
	shell->is_piped = 0;
	shell->pipe_in = -1;
	shell->pipe_out = -1;
}

void	handle_initial_redirection(t_shell *shell, int *i)
{
	int	j;

	free(shell->current_arg[0]);
	free(shell->current_arg[1]);
	j = 2;
	while (shell->current_arg[j] != NULL)
	{
		shell->current_arg[j - 2] = shell->current_arg[j];
		j++;
	}
	shell->current_arg[j - 2] = NULL;
	*i = 0;
	reset_shell_state(shell);
}

void	free_remaining_args(t_shell *shell, int i)
{
	int	j;

	j = i;
	while (shell->current_arg[j] != NULL)
	{
		free(shell->current_arg[j]);
		shell->current_arg[j] = NULL;
		j++;
	}
}

void	free_main_shell(t_shell *shell)
{
	int	i;

	if (shell == NULL || shell->current_arg == NULL)
		return ;
	i = 0;
	while (shell->current_arg[i] != NULL)
	{
		if (is_redirecion(shell->current_arg[i]) && i == 0 \
		&& shell->was_quoted[i] == 0)
			handle_initial_redirection(shell, &i);
		else if ((is_redirecion(shell->current_arg[i]) && i != 0 \
		&& shell->was_quoted[i] == 0) \
		|| (shell->current_arg[i][0] == '|' && shell->was_quoted[i] == 0 \
		&& shell->current_arg[i + 1] != NULL))
		{
			free_remaining_args(shell, i);
			return ;
		}
		i++;
	}
}
