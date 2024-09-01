/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:12:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/02 01:12:22 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* debug function to print shell instance data */
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

int	is_empty_or_whitespace(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	void_argc_argv(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	**env;

	env = init_env(envp);
	if (!env)
	{
		perror("init_env");
		return (1);
	}
	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		perror("malloc");
		free_array(env);
		return (1);
	}
	void_argc_argv(argc, argv);
	setup_signals();
	shell->exit_code = 0;
	while (1)
	{
		ft_init(shell);
		shell->current_line = readline("minishell$> ");
		if (shell->current_line == NULL)
		{
			printf("\b exit\n");
			break ;
		}
		if (is_empty_or_whitespace(shell->current_line))
		{
			free(shell->current_line);
			continue ;
		}
		if (ft_strlen(shell->current_line) > 0)
		{
			add_history(shell->current_line);
			parse_command(shell);
			if (is_builtin(shell))
				env = handle_builtin(shell, env);
			else
				execute_command(shell, env);
		}
		free_all_shells(shell->next);
		shell->next = NULL;
		free(shell->current_line);
		shell->current_line = NULL;
	}
	rl_clear_history();
	free_shell(shell);
	free_array(env);
	return (0);
}
