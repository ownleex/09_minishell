/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_and_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:43:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/06 17:47:21 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_parent_process(t_shell *shell, pid_t pid, int *status)
{
    //(void)pid;
    if (shell->pipe_out != -1)
        close(shell->pipe_out);
    if (shell->pipe_in != -1)
    {
        close(shell->pipe_in);
        shell->pipe_in = -1;
    }
    waitpid(pid, status, 0);
    if (WIFEXITED(*status))
        shell->exit_code = 128 + WEXITSTATUS(*status);
    else if (WIFSIGNALED(*status))
        handle_signaled_status(shell, *status);
}


void handle_fork(t_shell *shell, char **env, pid_t *pids, int index)
{
    pid_t pid;
    //int status = 0;

    pid = fork();
    if (pid == 0)  // Processus enfant
    {
        signal(SIGQUIT, SIG_DFL);  // Remet SIGQUIT à sa valeur par défaut
        signal(SIGINT, SIG_DFL);   // Remet SIGINT à sa valeur par défaut

        handle_redir(shell);  // Gestion des redirections
        execute_command_or_builtin(shell, env, pids);  // Exécution de la commande ou builtin

        exit(shell->exit_code);  // On termine proprement l'enfant
    }
    else if (pid < 0)  // Si fork échoue
    {
        perror("minishell");
        shell->exit_code = 1;
    }
    else  // Processus parent
    {
        pids[index] = pid;
        // On gère la fermeture des pipes dans le parent
        if (shell->pipe_out != -1)
            close(shell->pipe_out);
        if (shell->pipe_in != -1)
        {
            close(shell->pipe_in);
            shell->pipe_in = -1;
        }
    }
    signal(SIGQUIT, SIG_IGN);  // Ignore SIGQUIT dans le parent
}


