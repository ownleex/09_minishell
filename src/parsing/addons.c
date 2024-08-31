/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addons.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 14:15:07 by noldiane          #+#    #+#             */
/*   Updated: 2024/08/31 14:23:35 by noldiane         ###   ########.fr       */
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
			b = i;
			while (shell->current_arg[b] != NULL)
			{
				free(shell->current_arg[b]);
				b++;
			}
			shell->current_arg[i] = NULL;
			return ;
		}
		i++;
	}
}
