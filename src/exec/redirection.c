/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_and_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 00:36:07 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/02 23:40:16 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_output_file(t_shell *shell, char **env)
{
	int	outfile_fd;

	if (shell->append_output)
		outfile_fd = open(shell->output_file, O_WRONLY | O_CREAT | O_APPEND, \
		0644);
	else
		outfile_fd = open(shell->output_file, O_WRONLY | O_CREAT | O_TRUNC, \
		0644);
	if (outfile_fd == -1)
	{
		perror("minishell");
		shell->exit_code = 1;
		free_all_shells(shell);
		free_array(&env);
		exit(EXIT_FAILURE);
	}
	return (outfile_fd);
}

void	handle_input_redir(t_shell *shell, char **env)
{
	int	infile_fd;

	if (shell->input_file)
	{
		infile_fd = open(shell->input_file, O_RDONLY);
		if (infile_fd == -1)
		{
			perror("minishell");
			shell->exit_code = 1;
			free_all_shells(shell);
			free_array(&env);
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
}

void	handle_output_redir(t_shell *shell, char **env)
{
	int	outfile_fd;

	if (shell->output_file)
	{
		outfile_fd = open_output_file(shell, env);
		dup2(outfile_fd, STDOUT_FILENO);
		close(outfile_fd);
	}
	else if (shell->pipe_out != -1)
	{
		dup2(shell->pipe_out, STDOUT_FILENO);
		close(shell->pipe_out);
	}
}

void	handle_redir(t_shell *shell, char **env)
{
	handle_input_redir(shell, env);
	handle_output_redir(shell, env);
}
