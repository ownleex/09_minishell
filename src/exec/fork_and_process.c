/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:43:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/06 05:25:14 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent_process(t_shell *shell, pid_t pid, int *status)
{
	(void)pid;
	if (shell->pipe_out != -1)
		close(shell->pipe_out);
	if (shell->pipe_in != -1)
	{
		close(shell->pipe_in);
		shell->pipe_in = -1;
	}
	if (WIFEXITED(*status))
		shell->exit_code = WEXITSTATUS(*status);
	else if (WIFSIGNALED(*status))
		handle_signaled_status(shell, *status);
}

void	handle_fork(t_shell *shell, char **env, pid_t *pids, int index)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, handle_sigquit);
		handle_redir(shell);
		execute_command_or_builtin(shell, env, pids);
	}
	else if (pid < 0)
	{
		perror("minishell");
		shell->exit_code = 1;
	}
	else
	{
		pids[index] = pid;
		handle_parent_process(shell, pid, &status);
	}
	signal(SIGQUIT, SIG_IGN);
}
