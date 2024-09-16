/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:15:57 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/16 20:17:58 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command_or_builtin(t_shell *shell, char **env, pid_t *pids)
{
	int	exit_code;

	if (is_builtin(shell))
	{
		handle_builtin(shell, &env, pids);
		exit_code = shell->exit_code;
		free_all_shells(shell);
		free_array(&env);
		free(pids);
		exit(exit_code);
	}
	else
	{
		shell->command_path = find_command_path(shell, env);
		if (!shell->command_path)
		{
			write(STDERR_FILENO, "minishell: ", 12);
			write(STDERR_FILENO, \
			shell->current_cmd, ft_strlen(shell->current_cmd));
			write(STDERR_FILENO, ": Command not found\n", 20);
			free_all_shells(shell);
			free_array(&env);
			free(pids);
			exit(127);
		}
		if (execve(shell->command_path, shell->current_arg, env) == -1)
		{
			perror("minishell");
			free_all_shells(shell);
			free_array(&env);
			free(pids);
			exit(EXIT_FAILURE);
		}
	}
}

int	is_builtin_without_pipe_or_redirect(t_shell *shell)
{
	return (is_builtin(shell) && !shell->is_piped && \
	!shell->input_file && !shell->output_file);
}

void execute_command(t_shell *shell, char ***env)
{
    pid_t   *pids;
    int     i;
    int     status;
    t_shell *current_shell;
    int     last_status;
    int     num_procs;

    num_procs = 0;
    current_shell = shell;
    // Compter le nombre de processus à créer (non built-in ou built-in avec pipe/redirection)
    while (current_shell)
    {
        if (!is_builtin_without_pipe_or_redirect(current_shell))
            num_procs++;
        current_shell = current_shell->next;
    }

    // Allouer le tableau des PIDs seulement si nécessaire
    if (num_procs > 0)
    {
        pids = malloc(sizeof(pid_t) * num_procs);
        if (!pids)
        {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        pids = NULL; // Pas de processus enfant à créer
    }

    i = 0;
    current_shell = shell;
    while (current_shell)
    {
        handle_heredoc_if_needed(current_shell);
        handle_pipes_if_needed(current_shell);
        if (is_builtin_without_pipe_or_redirect(current_shell))
        {
            // Exécution du built-in sans fork
            handle_builtin(current_shell, env, pids);
            // Le exit_code est déjà mis à jour dans handle_builtin
        }
        else
        {
            // Exécution avec fork
            handle_fork(current_shell, *env, pids, i++);
        }
        free_args(current_shell);
        current_shell = current_shell->next;
    }

    // Gestion des processus enfants
    if (num_procs > 0)
    {
        last_status = 0;
        i = 0;
        while (i < num_procs)
        {
            waitpid(pids[i], &status, 0);
            if (i == num_procs - 1)
                last_status = status;
            i++;
        }
        // Mettre à jour shell->exit_code en fonction du statut du dernier processus enfant
        handle_signaled_status(shell, last_status);
        free(pids);
    }
    // Si num_procs == 0, aucun processus enfant n'a été créé
    // Le exit_code a déjà été mis à jour par le built-in exécuté sans fork
}

