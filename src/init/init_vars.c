/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:47:46 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/01 22:58:06 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_current_path(t_shell *shell)
{
	shell->current_path = getcwd(NULL, 0);
	if (!shell->current_path)
	{
		perror("getcwd");
		return (0);
	}
	return (1);
}

void	ft_init_variables(t_shell *shell)
{
	shell->current_line = NULL;
	shell->current_arg = NULL;
	shell->command_path = NULL;
	shell->current_cmd = NULL;
	shell->current_path = NULL;
	shell->target_path = NULL;
	shell->input_file = NULL;
	shell->output_file = NULL;
	shell->append_output = 0;
	shell->pipe_in = -1;
	shell->pipe_out = -1;
	shell->is_piped = 0;
	shell->has_single_quote = 0;
	shell->instance_count = 1;
	shell->is_heredoc = 0;
	shell->heredoc_delimiter = NULL;
	shell->next = NULL;
}

void	ft_init(t_shell *shell)
{
	ft_init_variables(shell);
	if (shell->current_path != NULL)
	{
		free(shell->current_path);
		shell->current_path = NULL;
	}
	if (!ft_set_current_path(shell))
	{
		free(shell);
		return ;
	}
}
