/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 23:03:51 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/21 22:38:49 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_shell(t_shell *shell)
{
	if (shell == NULL)
		return ;

	if (shell->current_path)
	{
		free(shell->current_path);
		shell->current_path = NULL;
	}
	if (shell->envp)
	{
		free_array(shell->envp);
		shell->envp = NULL;
	}
	if (shell->current_line)
	{
		free(shell->current_line);
		shell->current_line = NULL;
	}
	if (shell->command_path)
	{
		free(shell->command_path);
		shell->command_path = NULL;
	}
	if (shell->input_file)
	{
		free(shell->input_file);
		shell->input_file = NULL;
	}
	if (shell->output_file)
	{
		free(shell->output_file);
		shell->output_file = NULL;
	}
	free_args(shell);
	free(shell);
}
