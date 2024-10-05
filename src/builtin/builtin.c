/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:59:13 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/03 02:10:20 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_without_pipe_or_redirect(t_shell *shell)
{
	return (is_builtin(shell) && !shell->is_piped && \
	!shell->input_file && !shell->output_file);
}

int	is_builtin(t_shell *shell)
{
	if (shell->current_cmd == NULL)
		return (0);
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

void	handle_builtin(t_shell *shell, char ***env, pid_t *pids, int *pipes)
{
	if (ft_strcmp(shell->current_cmd, "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(shell->current_cmd, "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(shell->current_cmd, "env") == 0)
		ft_env(shell, *env);
	else if (ft_strcmp(shell->current_cmd, "exit") == 0)
		ft_exit(shell, *env, pids, pipes);
	else if (ft_strcmp(shell->current_cmd, "cd") == 0)
		*env = ft_cd(shell, *env);
	else if (ft_strcmp(shell->current_cmd, "export") == 0)
		*env = ft_export(shell, *env);
	else if (ft_strcmp(shell->current_cmd, "unset") == 0)
		*env = ft_unset(shell, *env);
}
