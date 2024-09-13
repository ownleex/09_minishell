/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:23:33 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/13 04:24:34 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_and_cleanup(t_shell *shell, char **env, int exit_code)
{
	printf("exit\n");
	free_redirections(shell);
	free_all_shells(shell);
	free_array(&env);
	rl_clear_history();
	exit(exit_code);
}

int	calculate_exit_code(t_shell *shell)
{
	int	exit_code;
	int	i;

	i = 0;
	if (shell->current_arg[1])
	{
		while (shell->current_arg[1][i])
		{
			if (!ft_isdigit(shell->current_arg[1][i++]))
			{
				printf("minishell: exit: %s: numeric argument required\n", \
				shell->current_arg[1]);
				return (2);
			}
		}
		exit_code = ft_atoi(shell->current_arg[1]);
	}
	else
		exit_code = shell->exit_code;
	return (exit_code);
}

void	ft_exit(t_shell *shell, char **env, pid_t *pids)
{
	int	exit_code;

	if (shell->current_arg[1] != NULL && shell->current_arg[2] != NULL)
	{
		printf("minishell: exit: too many arguments\n");
		shell->exit_code = 1;
		return ;
	}
	exit_code = calculate_exit_code(shell);
	free(pids);
	exit_and_cleanup(shell, env, exit_code);
}
