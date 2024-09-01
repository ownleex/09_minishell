/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:23:33 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/01 21:38:11 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell, char **env)
{
	int	i;

	i = 0;
	printf("exit\n");
	if (shell->current_arg[1])
	{
		while (shell->current_arg[1][i])
		{
			if (!isdigit(shell->current_arg[1][i]))
			{
				printf("bash: exit: %s: numeric argument required\n", \
				shell->current_arg[1]);
				exit(2);
			}
			i++;
		}
		exit(atoi(shell->current_arg[1]));
	}
	else
	{
		exit(0);
	}
	rl_clear_history();
	free_all_shells(shell);
	free_array(env);
}
