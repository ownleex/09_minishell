/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:12:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/24 03:04:32 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	// Ajoutez d'autres commandes intégrées ici
	return (0);
}

void	handle_builtin(char **args)
{
	if (strcmp(args[0], "echo") == 0)
	{
		for (int i = 1; args[i]; i++)
		{
			if (i > 1)
				printf(" ");
			printf("%s", args[i]);
		}
		//printf("\n");
	}
	// Ajoutez d'autres commandes intégrées ici
}

void	execute_command(char *line)
{
	pid_t	pid;
	char	**args;

	args = parse_command(line);
	if (args[0] == NULL)
	{
		free_args(args);
		return ;
	}

	if (is_builtin(args[0]))
	{
		handle_builtin(args);
		free_args(args);
		return ;
	}

	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("minishell");
	else
		waitpid(pid, NULL, 0);
	free_args(args);
}

int	main(void)
{
	char	*line;

	while (1)
	{
		write(1, "$> ", 3);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
		{
			write(1, "\n", 1);
			break ;
		}
		if (strlen(line) > 0)
		{
			execute_command(line);
		}
		free(line);
	}
	return (0);
}
