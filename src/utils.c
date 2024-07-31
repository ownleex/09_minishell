/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:03:51 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/31 22:49:44 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_args(t_minishell *shell)
{
	int	i;

	if (!shell || !shell->current_arg)
		return ;
	i = 0;
	while (shell->current_arg[i])
	{
		if (shell->current_arg[i] != NULL)
		{
			free(shell->current_arg[i]);
			shell->current_arg[i] = NULL;
		}
		i++;
	}
	free(shell->current_arg);
	shell->current_arg = NULL;
}
