/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:23:33 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/17 01:55:25 by ayarmaya         ###   ########.fr       */
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
	int		exit_code;
	char	*arg;

	arg = shell->current_arg[1];
	if (arg)
	{
		if (!is_numeric_argument(arg))
		{
			printf("minishell: exit: %s: numeric argument required\n", arg);
			free(pids);
			exit_and_cleanup(shell, env, 2, NULL);
		}
		if (shell->current_arg[2])
		{
			printf("minishell: exit: too many arguments\n");
			shell->exit_code = 1;
			return ;
		}
		exit_code = ft_atoi(arg);
		exit_and_cleanup(shell, env, exit_code, pids);
	}
	else
		exit_and_cleanup(shell, env, shell->exit_code, pids);
}
