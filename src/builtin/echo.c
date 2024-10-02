/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:56:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/02 16:17:10 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_shell *shell)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (shell->current_arg[i] && ft_strcmp(shell->current_arg[i], "-n") == 0)
	{
		newline = 0;
		i++;
	}
	while (shell->current_arg[i])
	{
		printf("%s", shell->current_arg[i]);
		if (shell->current_arg[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	shell->exit_code = 0;
}
