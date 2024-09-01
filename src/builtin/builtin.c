/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:59:13 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/01 22:11:02 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_shell *shell)
{
	if (ft_strcmp(shell->current_cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(shell->current_cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(shell->current_cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(shell->current_cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(shell->current_cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(shell->current_cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(shell->current_cmd, "unset") == 0)
		return (1);
	return (0);
}

char	**handle_builtin(t_shell *shell, char **env)
{
	if (ft_strcmp(shell->current_cmd, "echo") == 0)
		ft_echo(shell, env);
	else if (ft_strcmp(shell->current_cmd, "pwd") == 0)
		ft_pwd();
	else if (ft_strcmp(shell->current_cmd, "env") == 0)
		ft_env(shell, env);
	else if (ft_strcmp(shell->current_cmd, "exit") == 0)
		ft_exit(shell, env);
	else if (ft_strcmp(shell->current_cmd, "cd") == 0)
		env = ft_cd(shell, env);
	else if (ft_strcmp(shell->current_cmd, "export") == 0)
		env = ft_export(shell, env);
	else if (ft_strcmp(shell->current_cmd, "unset") == 0)
		env = ft_unset(shell, env);
	return (env);
}
