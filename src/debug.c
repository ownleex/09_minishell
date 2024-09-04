/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 22:02:12 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/04 22:02:30 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_shell_instance(t_shell *shell)
{
	int	index;
	int	arg_index;

	index = 0;
	while (shell)
	{
		printf("\nShell instance #%d:\n", index);
		printf("  current_line: %s\n", shell->current_line ? shell->current_line : "(null)");
		printf("  current_cmd: %s\n", shell->current_cmd ? shell->current_cmd : "(null)");
		if (shell->current_arg)
		{
			printf("  current_arg:\n");
			arg_index = 0;
			while (shell->current_arg[arg_index])
			{
				printf("    arg[%d]: %s\n", arg_index, shell->current_arg[arg_index]);
				arg_index++;
			}
		}
		else
			printf("  current_arg: (null)\n");
		printf("  command_path: %s\n", shell->command_path ? shell->command_path : "(null)");
		printf("  current_path: %s\n", shell->current_path ? shell->current_path : "(null)");
		printf("  target_path: %s\n", shell->target_path ? shell->target_path : "(null)");
		printf("  input_file: %s\n", shell->input_file ? shell->input_file : "(null)");
		printf("  output_file: %s\n", shell->output_file ? shell->output_file : "(null)");
		printf("  append_output: %d\n", shell->append_output);
		printf("  pipe_in: %d\n", shell->pipe_in);
		printf("  pipe_out: %d\n", shell->pipe_out);
		printf("  is_piped: %d\n", shell->is_piped);
		printf("  exit_code: %d\n", shell->exit_code);
		printf("  instance_count: %d\n", shell->instance_count);
		printf("  next: %p\n", (void *)shell->next);
		printf("\n");
		shell = shell->next;
		index++;
	}
}