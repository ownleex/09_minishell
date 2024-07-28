/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:12:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/28 21:44:59 by ayarmaya         ###   ########.fr       */
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

char	*find_command_path(char *cmd, char **envp)
{
	char	**path_split;
	char	*path = NULL;
	char	*full_path;
	int	i;

	while (*envp)
	{
		path_split = ft_split(*envp, '=');
		if (strcmp(path_split[0], "PATH") == 0)
		{
			path = strdup(path_split[1]);
			free_array(path_split);
			break;
		}
		free_array(path_split);
		envp++;
	}
	if (!path)
		return (NULL);
	path_split = ft_split(path, ':');
	free(path);
	i = 0;
	while (path_split[i])
	{
		full_path = ft_strjoin(path_split[i], "/");
		full_path = ft_strjoin(full_path, cmd);
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

char	**parse_command(char *line)
{
	char	**args;

	args = ft_split(line, ' ');
	return (args);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

int	is_builtin(char *command)
{
	if (strcmp(command, "echo") == 0)
		return (1);
	return (0);
}

void	handle_builtin(char **args)
{
	int	i;

	if (strcmp(args[0], "echo") == 0)
	{
		i = 1;
		while (args[i])
		{
			if (i > 1)
				printf(" ");
			printf("%s", args[i]);
			i++;
		}
		printf("\n");
	}
}

void	execute_command(char *line, char **envp)
{
	pid_t	pid;
	char	**args;
	char	*cmd_path;

	args = parse_command(line);
	if (is_builtin(args[0]))
	{
		handle_builtin(args);
		free_args(args);
		return ;
	}
	cmd_path = find_command_path(args[0], envp);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "Command not found: %s\n", args[0]);
		free_args(args);
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, envp) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("minishell");
	else
		waitpid(pid, NULL, 0);
	free(cmd_path);
	free_args(args);
}


int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("minishell$> ");
		if (line == NULL)
		{
			printf("\n");
			break;
		}
		if (strlen(line) > 0)
		{
			add_history(line);
			execute_command(line, envp);
		}
		free(line);
	}
	return (0);
}
