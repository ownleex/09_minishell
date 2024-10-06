/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:15:57 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/06 03:16:06 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(t_shell *shell)
{
	int	count;

	count = 0;
	while (shell)
	{
		count++;
		shell = shell->next;
	}
	return (count);
}

void	cleanup_and_exit(int exit_code, t_shell *shell, char **env, pid_t *pids)
{
	if (shell)
		free_all_shells(shell);
	if (env)
		free_array(&env);
	if (pids)
		free(pids);
	exit(exit_code);
}

void	exec_commd_builtin(t_shell *shell, char **env, pid_t *pids, int *pipes)
{
	if (is_builtin(shell))
	{
		handle_builtin(shell, &env, pids, pipes);
		free(pipes);
		cleanup_and_exit(shell->exit_code, shell, env, pids);
	}
	else
	{
		shell->command_path = find_command_path(shell, env);
		if (!shell->command_path)
		{
			write(STDERR_FILENO, "minishell: ", 12);
			write(STDERR_FILENO, shell->current_cmd, \
			ft_strlen(shell->current_cmd));
			write(STDERR_FILENO, ": Command not found\n", 21);
			free(pipes);
			cleanup_and_exit(127, shell, env, pids);
		}
		if (execve(shell->command_path, shell->current_arg, env) == -1)
		{
			perror("minishell");
			free(pipes);
			cleanup_and_exit(EXIT_FAILURE, shell, env, pids);
		}
	}
}

void	execute_command_iteration(t_shell *current_shell, char ***env, \
t_context *context)
{
	handle_heredoc_if_needed(current_shell);
	if (is_builtin_without_pipe_or_redirect(current_shell) && \
	context->num_cmds == 1)
	{
		handle_builtin(current_shell, env, context->pids, context->pipes);
		return ;
	}
	context->pids[context->i] = fork();
	if (context->pids[context->i] == 0)
	{
		execute_child_process(current_shell, *env, context);
	}
	else if (context->pids[context->i] < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	context->i++;
}

void	execute_command(t_shell *shell, char ***env)
{
	t_context	context;
	t_shell		*current_shell;

	current_shell = NULL;
	init_context(&context, shell);
	current_shell = shell;
	while (current_shell)
	{
		execute_command_iteration(current_shell, env, &context);
		current_shell = current_shell->next;
	}
	close_all_pipes(context.pipes, 2 * (context.num_cmds - 1));
	wait_for_processes(context.pids, context.i, shell);
	free(context.pipes);
	free(context.pids);
	signal(SIGQUIT, SIG_IGN);
}
