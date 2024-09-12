/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 00:41:59 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/12 03:01:11 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_ctrl_d(t_shell *shell, char *line)
{
	if (!line)
	{
		printf("minishell: warning: ");
		printf("here-document delimited by end-of-file ");
		printf("(wanted '%s')\n", shell->heredoc_delimiter);
		return (1);
	}
	return (0);
}

void	handle_heredoc(t_shell *shell)
{
	int		pipe_fd[2];
	char	*line;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		line = readline("> ");
		if (heredoc_ctrl_d(shell, line))
			break ;
		if (ft_strcmp(line, shell->heredoc_delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	shell->pipe_in = pipe_fd[0];
}

void	handle_heredoc_if_needed(t_shell *shell)
{
	if (shell->is_heredoc)
		handle_heredoc(shell);
	shell->is_heredoc = 0;
}
