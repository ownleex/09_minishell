/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:23:33 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/16 23:54:53 by ayarmaya         ###   ########.fr       */
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

int	is_numeric_argument(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
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
	long	exit_code;
	char	*arg;

	arg = shell->current_arg[1];
	if (arg)
	{
		if (!is_numeric_argument(arg))
			return (255);
		exit_code = ft_atol(arg);
		exit_code = exit_code % 256;
		if (exit_code < 0)
			exit_code += 256;
		return ((int)exit_code);
	}
	return (shell->exit_code);
}

void	ft_exit(t_shell *shell, char **env, pid_t *pids)
{
	int	exit_code;

	if (shell->current_arg[1] && shell->current_arg[2])
	{
		printf("minishell: exit: too many arguments\n");
		shell->exit_code = 1;
		return ;
	}
	exit_code = calculate_exit_code(shell);
	if (exit_code == 255 && shell->current_arg[1])
	{
		printf("minishell: exit: %s: numeric argument required\n", \
		shell->current_arg[1]);
		free(pids);
		exit_and_cleanup(shell, env, exit_code);
	}
	free(pids);
	exit_and_cleanup(shell, env, exit_code);
}
