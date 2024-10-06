/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:43:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/06 05:03:58 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	initialize_pids(t_shell *shell, pid_t **pids)
{
	int		num_procs;
	t_shell	*current_shell;

	num_procs = 0;
	current_shell = shell;
	while (current_shell)
	{
		if (!is_builtin_without_pipe_or_redirect(current_shell))
			num_procs++;
		current_shell = current_shell->next;
	}
	if (num_procs > 0)
	{
		*pids = malloc(sizeof(pid_t) * num_procs);
		if (!(*pids))
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	}
	else
		*pids = NULL;
	return (num_procs);
}

void	wait_for_processes(pid_t *pids, int num_procs, t_shell *shell)
{
	int	i;
	int	status;
	int	last_status;

	if (num_procs == 0)
		return ;
	last_status = 0;
	i = 0;
	while (i < num_procs)
	{
		waitpid(pids[i], &status, 0);
		if (i == num_procs - 1)
			last_status = status;
		i++;
	}
	handle_signaled_status(shell, last_status);
}

void	execute_child_process(t_shell *current_shell, char **env, \
t_context *context)
{
	int	j;

	j = 0;
	signal(SIGQUIT, handle_sigquit);
	if (context->i != 0)
		dup2(context->pipes[(context->i - 1) * 2], STDIN_FILENO);
	if (context->i != context->num_cmds - 1)
		dup2(context->pipes[context->i * 2 + 1], STDOUT_FILENO);
	while (j < 2 * (context->num_cmds - 1))
	{
		close(context->pipes[j]);
		j++;
	}
	handle_redir(current_shell, env, context->pids, context->pipes);
	exec_commd_builtin(current_shell, env, context->pids, context->pipes);
	exit(current_shell->exit_code);
}
