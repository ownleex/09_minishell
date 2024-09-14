/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:15:07 by noldiane          #+#    #+#             */
/*   Updated: 2024/09/14 00:38:37 by ayarmaya         ###   ########.fr       */
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

void	free_main_shell(t_shell *shell)
{
	int	i;
	int	b;

	if (shell == NULL || shell->current_arg == NULL)
		return ;
	i = 0;
	while (shell->current_arg[i] != NULL)
	{
		if ((shell->current_arg[i][0] == '|' && \
		shell->current_arg[i + 1] != NULL) || \
		(is_redirecion(shell->current_arg[i]) && \
		shell->current_arg[i + 1] != NULL))
		{
			if (is_redirecion(shell->current_arg[i]) && i == 0)
			{
				free(shell->current_arg[0]);
				shell->current_arg[0] = ft_strdup(shell->current_arg[2]);
				free(shell->current_arg[2]);
				free(shell->current_arg[1]);
				shell->current_arg[1] = NULL;
				i = 3;
				free_all_shells(shell->next);
				shell->is_piped = 0;
				shell->pipe_in = -1;
				shell->pipe_out = -1;
				shell->next = NULL;
				continue ;
			}
			else if (is_redirecion(shell->current_arg[i]))
			{
				shell->is_piped = 0;
				shell->pipe_in = -1;
				shell->pipe_out = -1;
				free_all_shells(shell->next);
				shell->next = NULL;
			}
			b = i;
			while (shell->current_arg[b] != NULL)
			{
				free(shell->current_arg[b]);
				shell->current_arg[b] = NULL;
				b++;
			}
			return ;
		}
		i++;
	}
}
