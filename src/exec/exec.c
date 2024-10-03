/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:15:57 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/03 02:20:03 by ayarmaya         ###   ########.fr       */
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

void	execute_command(t_shell *shell, char ***env)
{
	int		num_cmds;
	int		*pipes;
	pid_t	*pids;
	int		i;
	t_shell	*current_shell;

	num_cmds = count_commands(shell);
	pipes = malloc(sizeof(int) * 2 * (num_cmds - 1));
	pids = malloc(sizeof(pid_t) * num_cmds);
	if (!pipes || !pids)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < num_cmds - 1; i++)
	{
		if (pipe(pipes + i * 2) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}
	current_shell = shell;
	i = 0;
	while (current_shell)
	{
		if (is_builtin_without_pipe_or_redirect(current_shell) && num_cmds == 1)
		{
			handle_builtin(current_shell, env, NULL, pipes);
			current_shell = current_shell->next;
			continue ;
		}
		pid_t pid = fork();
		if (pid == 0)
		{
			signal(SIGQUIT, handle_sigquit);
			if (i != 0)
				dup2(pipes[(i - 1) * 2], STDIN_FILENO);
			if (i != num_cmds - 1)
				dup2(pipes[i * 2 + 1], STDOUT_FILENO);
			for (int j = 0; j < 2 * (num_cmds - 1); j++)
				close(pipes[j]);
			handle_redir(current_shell, *env);
			exec_commd_builtin(current_shell, *env, pids, pipes);
			exit(current_shell->exit_code);
		}
		else if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		pids[i] = pid;
		current_shell = current_shell->next;
		i++;
	}
	for (int j = 0; j < 2 * (num_cmds - 1); j++)
		close(pipes[j]);
	wait_for_processes(pids, i, shell);
	free(pipes);
	free(pids);
	signal(SIGQUIT, SIG_IGN);
}
