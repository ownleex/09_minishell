/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:15:57 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/19 00:05:33 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	execute_command_or_builtin(t_shell *shell, char **env, pid_t *pids)
{
	int	exit_code;

	if (is_builtin(shell))
	{
		handle_builtin(shell, &env, pids);
		exit_code = shell->exit_code;
		cleanup_and_exit(exit_code, shell, env, pids);
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
			cleanup_and_exit(127, shell, env, pids);
		}
		if (execve(shell->command_path, shell->current_arg, env) == -1)
		{
			perror("minishell");
			cleanup_and_exit(EXIT_FAILURE, shell, env, pids);
		}
	}
}

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
	free(pids);
}

void	execute_command(t_shell *shell, char ***env)
{
	pid_t	*pids;
	int		num_procs;
	int		i;
	t_shell	*current_shell;

	num_procs = initialize_pids(shell, &pids);
	i = 0;
	current_shell = shell;
	while (current_shell)
	{
		handle_heredoc_if_needed(current_shell);
		handle_pipes_if_needed(current_shell);
		if (is_builtin_without_pipe_or_redirect(current_shell))
			handle_builtin(current_shell, env, pids);
		else
			handle_fork(current_shell, *env, pids, i++);
		free_args(current_shell);
		current_shell = current_shell->next;
	}
	if (num_procs > 0)
		wait_for_processes(pids, num_procs, shell);
}
