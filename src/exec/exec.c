/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:15:57 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/01 22:20:42 by ayarmaya         ###   ########.fr       */
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
		if (ft_strcmp(path_split[0], "PATH") == 0)
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

void	handle_heredoc(t_shell *shell)
{
    int     pipe_fd[2];
    char    *line;

    if (pipe(pipe_fd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        line = readline("> ");
        if (!line || ft_strcmp(line, shell->heredoc_delimiter) == 0)
        {
            free(line);
            break;
        }
        write(pipe_fd[1], line, ft_strlen(line));
        write(pipe_fd[1], "\n", 1);
        free(line);
    }
    close(pipe_fd[1]);
    shell->pipe_in = pipe_fd[0]; // Rediriger l'entrée de la commande vers le pipe
}

void execute_command(t_shell *shell, char **env)
{
    pid_t   pid;
    int     status;

    while (shell)
    {
        if (shell->is_heredoc)
            handle_heredoc(shell);

        pid = fork();
        if (pid == 0)
        {
            // Gestion des redirections d'entrée
            if (shell->input_file)
            {
                int infile_fd = open(shell->input_file, O_RDONLY);
                if (infile_fd == -1)
                {
                    perror("open input_file");
                    exit(EXIT_FAILURE);
                }
                dup2(infile_fd, STDIN_FILENO);
                close(infile_fd);
            }
            else if (shell->pipe_in != -1)
            {
                dup2(shell->pipe_in, STDIN_FILENO);
                close(shell->pipe_in);
            }

            // Gestion des redirections de sortie et pipes (déjà présent)
            // ...

            if (is_builtin(shell))
                handle_builtin(shell, env);
            else
            {
                shell->command_path = find_command_path(shell, env);
                if (!shell->command_path)
                {
                    write(STDERR_FILENO, "bash: ", 6);
                    write(STDERR_FILENO, shell->current_cmd, ft_strlen(shell->current_cmd));
                    write(STDERR_FILENO, ": Command not found\n", 20);
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
            waitpid(pid, &status, 0);
            if (WIFEXITED(status))
                shell->exit_code = WEXITSTATUS(status);
            else if (WIFSIGNALED(status))
                shell->exit_code = 128 + WTERMSIG(status);
        }

        // Libération de la mémoire associée à l'instance actuelle
        // ...
        shell = shell->next;
    }
}
