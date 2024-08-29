/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:59:13 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/29 01:55:40 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_shell *shell)
{
	if (ft_strncmp(shell->current_cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "unset", 5) == 0)
		return (1);
	return (0);
}

char	**handle_builtin(t_shell *shell, char **env)
{
	if (ft_strncmp(shell->current_cmd, "echo", 4) == 0)
		ft_echo(shell, env);
	else if (ft_strncmp(shell->current_cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(shell->current_cmd, "env", 3) == 0)
		ft_env(shell, env);
	else if (ft_strncmp(shell->current_cmd, "exit", 4) == 0)
		ft_exit(shell, env);
	else if (ft_strncmp(shell->current_cmd, "cd", 2) == 0)
		env = ft_cd(shell, env);
	else if (ft_strncmp(shell->current_cmd, "export", 6) == 0)
		env = ft_export(shell, env);
	else if (ft_strncmp(shell->current_cmd, "unset", 5) == 0)
		env = ft_unset(shell, env);
	return (env);
}
