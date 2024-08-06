/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nolans <nolans@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:19:50 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/06 17:00:47 by nolans           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

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
