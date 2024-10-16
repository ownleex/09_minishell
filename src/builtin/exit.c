/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:23:33 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/03 02:14:40 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_and_cleanup(t_shell *shell, char **env, int exit_code, pid_t *pids)
{
	printf("exit\n");
	if (pids)
		free(pids);
	free_redirections(shell);
	free_all_shells(shell);
	free_array(&env);
	rl_clear_history();
	exit(exit_code);
}

int	is_numeric_argument(const char *str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_exit(t_shell *shell, char **env, pid_t *pids, int *pipes)
{
	char	*arg;

	arg = shell->current_arg[1];
	if (arg)
	{
		if (!is_numeric_argument(arg))
		{
			printf("minishell: exit: %s: numeric argument required\n", arg);
			free(pipes);
			exit_and_cleanup(shell, env, 2, pids);
		}
		if (shell->current_arg[2])
		{
			printf("minishell: exit: too many arguments\n");
			shell->exit_code = 1;
			return ;
		}
		free(pipes);
		exit_and_cleanup(shell, env, ft_atoi(arg), pids);
	}
	else
	{
		free(pipes);
		exit_and_cleanup(shell, env, shell->exit_code, pids);
	}
}
