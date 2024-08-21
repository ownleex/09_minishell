/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:12:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/22 01:18:37 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* debug function to print shell instance data */
void	print_shell_instance(t_shell *shell)
{
	int	index;

	index = 0;
	while (shell)
	{
		printf("\nShell instance #%d:\n", index);
		printf("  current_line: %s\n", shell->current_line ? shell->current_line : "(null)");
		printf("  current_cmd: %s\n", shell->current_cmd ? shell->current_cmd : "(null)");
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

void	ft_init(t_shell *shell, char **envp)
{
	int		i;
	int		envp_len;

	shell->current_line = NULL;
	shell->current_arg = NULL;
	shell->command_path = NULL;
	shell->current_cmd = NULL;
	shell->current_path = NULL;
	shell->target_path = NULL;
	shell->exit_code = 0;
	shell->input_file = NULL;
	shell->output_file = NULL;
	shell->append_output = 0;
	shell->pipe_in = -1;
	shell->pipe_out = -1;
	shell->is_piped = 0;
	shell->next = NULL;
	envp_len = 0;
	while (envp[envp_len])
		envp_len++;
	shell->envp = (char **)malloc(sizeof(char *) * (envp_len + 1));
	if (!shell->envp)
	{
		perror("malloc");
		free(shell);
		return ;
	}
	i = 0;
	while (i < envp_len)
	{
		shell->envp[i] = ft_strdup(envp[i]);
		if (!shell->envp[i])
		{
			perror("strdup");
			while (i > 0)
				free(shell->envp[--i]);
			free(shell->envp);
			free(shell);
			return ;
		}
		i++;
	}
	shell->envp[i] = NULL;
	shell->current_path = getcwd(NULL, 0);
	if (!shell->current_path)
	{
		perror("getcwd");
		i = 0;
		while (shell->envp[i])
			free(shell->envp[i++]);
		free(shell->envp);
		free(shell);
		return ;
	}
}

void	void_argc_argv(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		perror("malloc");
		return (1);
	}
	void_argc_argv(argc, argv);
	ft_init(shell, envp);
	setup_signals();
	while (1)
	{
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
			print_shell_instance(shell); //debug
			execute_command(shell);
		}
		free_all_shells(shell->next);
		shell->next = NULL;
		free(shell->current_line);
		shell->current_line = NULL;
	}
	rl_clear_history();
	free_shell(shell);
	return (0);
}

