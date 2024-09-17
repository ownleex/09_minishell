/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 19:19:50 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/17 02:48:34 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char ***array_ptr)
{
	int		i;
	char	**array;

	if (!array_ptr || !*array_ptr)
		return ;
	array = *array_ptr;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	*array_ptr = NULL;
}

void	free_args(t_shell *shell)
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
	if (shell->has_single_quote)
	{
		free(shell->has_single_quote);
		shell->has_single_quote = NULL;
	}
	if (shell->was_quoted)
	{
		free(shell->was_quoted);
		shell->was_quoted = NULL;
	}
}
