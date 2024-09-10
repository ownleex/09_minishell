/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:03:51 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/09 23:44:35 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	void_argc_argv(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

void	free_redirections(t_shell *shell)
{
	if (shell->output_file)
	{
		free(shell->output_file);
		shell->output_file = NULL;
	}
	if (shell->input_file)
	{
		free(shell->input_file);	
		shell->input_file = NULL;
	}
	if (shell->heredoc_delimiter)
	{
		free(shell->heredoc_delimiter);
		shell->heredoc_delimiter = NULL;
	}
}

void	free_all_shells(t_shell *shell)
{
	t_shell	*temp;

	while (shell)
	{
		temp = shell->next;
		free_shell(shell);
		shell = temp;
	}
}

void	free_null_args(char *args)
{
	free(args);
	args = NULL;
}

void	free_shell(t_shell *shell)
{
	if (shell == NULL)
		return ;
	if (shell->current_line)
		free_null_args(shell->current_line);
	if (shell->command_path)
		free_null_args(shell->command_path);
	if (shell->input_file)
		free_null_args(shell->input_file);
	if (shell->output_file)
		free_null_args(shell->output_file);
	if (shell->heredoc_delimiter)
		free_null_args(shell->heredoc_delimiter);
	free_args(shell);
	free(shell);
}
