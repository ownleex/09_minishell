/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:43:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/19 00:25:11 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_process(t_shell *shell)
{
	if (shell->pipe_out != -1)
		close(shell->pipe_out);
	if (shell->pipe_in != -1)
	{
		close(shell->pipe_in);
		shell->pipe_in = -1;
	}
}

void	handle_fork(t_shell *shell, char **env, pid_t *pids, int index)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, handle_sigquit);
		handle_redir(shell, env);
		execute_command_or_builtin(shell, env, pids);
		exit(shell->exit_code);
	}
	else if (pid < 0)
	{
		perror("minishell");
		shell->exit_code = 1;
	}
	else
	{
		pids[index] = pid;
		handle_parent_process(shell);
	}
	signal(SIGQUIT, SIG_IGN);
}
