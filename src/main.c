/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:12:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/28 22:13:57 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i = 0;

	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

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

void	parse_command(t_minishell *shell)
{
	shell->current_args = ft_split(shell->current_line, ' ');
	shell->current_cmd = shell->current_args[0];
}

void	free_args(t_minishell *shell)
{
	int	i = 0;

	while (shell->current_args[i])
	{
		free(shell->current_args[i]);
		i++;
	}
	free(shell->current_args);
}

int	is_builtin(t_minishell *shell)
{
	if (strcmp(shell->current_cmd, "echo") == 0)
		return (1);
	return (0);
}

void	handle_builtin(t_minishell *shell)
{
	int	i = 1;

	if (strcmp(shell->current_cmd, "echo") == 0)
	{
		while (shell->current_args[i])
		{
			if (i > 1)
				printf(" ");
			printf("%s", shell->current_args[i]);
			i++;
		}
		printf("\n");
	}
}

void	execute_command(t_minishell *shell)
{
	pid_t	pid;

	parse_command(shell);
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

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.envp = envp;
	while (1)
	{
		shell.current_line = readline("minishell$> ");
		if (shell.current_line == NULL)
		{
			printf("\n");
			break;
		}
		if (strlen(shell.current_line) > 0)
		{
			add_history(shell.current_line);
			execute_command(&shell);
		}
		free(shell.current_line);
	}
	return (0);
}
