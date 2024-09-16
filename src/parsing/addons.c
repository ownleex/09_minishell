/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:15:07 by noldiane          #+#    #+#             */
/*   Updated: 2024/09/15 23:58:59 by ayarmaya         ###   ########.fr       */
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

void free_main_shell(t_shell *shell)
{
	int i;
	int j;

	if (shell == NULL || shell->current_arg == NULL)
		return;

	i = 0;
	while (shell->current_arg[i] != NULL)
	{
		// Handling if redirection is at the start
		if (is_redirecion(shell->current_arg[i]) && i == 0)
		{
			// Free the redirection tokens
			free(shell->current_arg[0]); // "<" or ">"
			free(shell->current_arg[1]); // The file (e.g., "Makefile")

			// Shift the arguments to the left
			j = 2; // Start shifting from index 2
			while (shell->current_arg[j] != NULL)
			{
				shell->current_arg[j - 2] = shell->current_arg[j];
				j++;
			}
			shell->current_arg[j - 2] = NULL; // Null-terminate the array

			// Reset indices and states
			i = 0;
			free_all_shells(shell->next);
			shell->is_piped = 0;
			shell->pipe_in = -1;
			shell->pipe_out = -1;
			shell->next = NULL;
			continue;
		}
		else if ((is_redirecion(shell->current_arg[i]) && i != 0) ||
				 (shell->current_arg[i][0] == '|' && shell->current_arg[i + 1] != NULL))
		{
			// If it's a redirection or a pipe in the middle of the arguments, we can stop freeing here
			j = i;
			while (shell->current_arg[j] != NULL)
			{
				free(shell->current_arg[j]);
				shell->current_arg[j] = NULL;
				j++;
			}
			return;
		}
		i++;
	}
}
