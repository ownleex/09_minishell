/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:15:57 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/29 00:43:09 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_command_path(t_minishell *shell)
{
	char	**path_split;
	char	*path = NULL;
	char	*full_path;
	int	i = 0;

	while (shell->envp[i])
	{
		path_split = ft_split(shell->envp[i], '=');
		if (strcmp(path_split[0], "PATH") == 0)
		{
			path = strdup(path_split[1]);
			free_array(path_split);
			break;
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
		full_path = ft_strjoin(full_path, shell->current_cmd);
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

void	execute_command(t_minishell *shell)
{
	pid_t	pid;

	if (is_builtin(shell))
	{
		handle_builtin(shell);
		free_args(shell);
		return;
	}
	shell->command_path = find_command_path(shell);
	if (shell->command_path == NULL)
	{
		fprintf(stderr, "Command not found: %s\n", shell->current_cmd);
		free_args(shell);
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(shell->command_path, shell->current_args, shell->envp) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("minishell");
	else
		waitpid(pid, NULL, 0);
	free(shell->command_path);
	free_args(shell);
}