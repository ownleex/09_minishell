/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:15:57 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/26 23:25:27 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_command_path(t_shell *shell, char **env)
{
	char	**path_split;
	char	*path;
	char	*full_path;
	char	*temp;
	int		i;

	path = NULL;
	i = 0;
	if (access(shell->current_cmd, X_OK) == 0)
	{
		return (ft_strdup(shell->current_cmd));
	}
	while (env[i])
	{
		path_split = ft_split(env[i], '=');
		if (ft_strncmp(path_split[0], "PATH", 4) == 0)
		{
			path = ft_strdup(path_split[1]);
			free_array(path_split);
			break ;
		}
		free_array(path_split);
		i++;
	}
	if (!path)
		return (NULL);
	path_split = ft_split(path, ':');
	free(path);
	i = 0;
	while (path_split[i])
	{
		full_path = ft_strjoin(path_split[i], "/");
		temp = full_path;
		full_path = ft_strjoin(full_path, shell->current_cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			free_array(path_split);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(path_split);
	return (NULL);
}

void	execute_command(t_shell *shell, char **env)
{
	pid_t	pid;
	int		status;
	int		pipe_fds[2];

	while (shell)
	{
		if (shell->is_piped)
		{
			if (pipe(pipe_fds) == -1)
			{
				perror("pipe");
				shell->exit_code = 1;
				return ;
			}
			shell->pipe_out = pipe_fds[1];
			shell->next->pipe_in = pipe_fds[0];
		}
		pid = fork();
		if (pid == 0)
		{
			if (shell->pipe_in != -1)
			{
				dup2(shell->pipe_in, STDIN_FILENO);
				close(shell->pipe_in);
			}
			if (shell->pipe_out != -1)
			{
				dup2(shell->pipe_out, STDOUT_FILENO);
				close(shell->pipe_out);
			}
			if (shell->pipe_out != -1)
				close(shell->pipe_out);
			if (shell->pipe_in != -1)
				close(shell->pipe_in);
			if (is_builtin(shell))
			{
				handle_builtin(shell, env);
				free_args(shell);
				exit(shell->exit_code);
			}
			else
			{
				shell->command_path = find_command_path(shell, env);
				if (!shell->command_path)
				{
					write(STDERR_FILENO, "bash: ", 7);
					write(STDERR_FILENO, shell->current_cmd, ft_strlen(shell->current_cmd));
					write(STDERR_FILENO, ": Command not found\n", 21);
					exit(127);
				}
				if (execve(shell->command_path, shell->current_arg, env) == -1)
				{
					perror("minishell");
					exit(EXIT_FAILURE);
				}
			}
		}
		else if (pid < 0)
		{
			perror("minishell");
			shell->exit_code = 1;
		}
		else
		{
			if (shell->pipe_out != -1)
				close(shell->pipe_out);
			if (shell->pipe_in != -1)
				close(shell->pipe_in);
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				shell->exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_code = 128 + WTERMSIG(status);
		}
		shell = shell->next;
	}
}
