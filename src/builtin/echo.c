/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:56:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/02 22:20:11 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(t_shell *shell, int i)
{
	while (shell->current_arg[i])
	{
		printf("%s", shell->current_arg[i]);
		if (shell->current_arg[i + 1])
			printf(" ");
		i++;
	}
}

void	ft_echo(t_shell *shell)
{
	int	i;
	int	newline;
	int	j;

	i = 1;
	newline = 1;
	while (shell->current_arg[i] && shell->current_arg[i][0] == '-')
	{
		j = 1;
		while (shell->current_arg[i][j] == 'n')
			j++;
		if (shell->current_arg[i][j] == '\0' && j > 1)
		{
			newline = 0;
			i++;
		}
		else
			break ;
	}
	print_args(shell, i);
	if (newline)
		printf("\n");
	shell->exit_code = 0;
}
