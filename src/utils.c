/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:03:51 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/13 15:23:53 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	void_argc_argv(int argc, char **argv)
{
	(void)argc;
	(void)argv;
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

void	free_null_args(char **args)
{
	if (args && *args)
	{
		free(*args);
		*args = NULL;
	}
}

void	free_redirections(t_shell *shell)
{
	if (shell == NULL)
		return ;
	free_null_args(&shell->output_file);
	free_null_args(&shell->input_file);
	free_null_args(&shell->heredoc_delimiter);
}

void	free_shell(t_shell *shell)
{
	if (shell == NULL)
		return ;
	free_null_args(&shell->current_line);
	free_null_args(&shell->command_path);
	free_null_args(&shell->input_file);
	free_null_args(&shell->output_file);
	free_null_args(&shell->heredoc_delimiter);
	free_args(shell);
	free(shell);
}
