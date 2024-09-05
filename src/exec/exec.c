/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:15:57 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/05 06:39:57 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_command_or_builtin(t_shell *shell, char **env)
{
	if (is_builtin(shell))
	{
		env = handle_builtin(shell, env);
		free_args(shell);
		exit(shell->exit_code);
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
			exit(127);
		}
		if (execve(shell->command_path, shell->current_arg, env) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
}

int	is_builtin_without_pipe_or_redirect(t_shell *shell)
{
	return (is_builtin(shell) && !shell->is_piped && \
	!shell->input_file && !shell->output_file);
}

char	**execute_command(t_shell *shell, char **env)
{
	while (shell)
	{
		handle_heredoc_if_needed(shell);
		handle_pipes_if_needed(shell);
		if (is_builtin_without_pipe_or_redirect(shell))
		{
			env = handle_builtin(shell, env);
			free_args(shell);
			shell->exit_code = 0;
		}
		else
			handle_fork(shell, env);
		free_args(shell);
		shell = shell->next;
	}
	return (env);
}
