/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:12:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/04 02:26:56 by ayarmaya         ###   ########.fr       */
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

int is_invalid_syntax(t_shell *shell) {
    int len = ft_strlen(shell->current_line);
    int i = 0;
    int single_quote_open = 0;
    int double_quote_open = 0;

    // Ignore les espaces au début de la commande
    while (shell->current_line[i] == ' ' && shell->current_line[i] != '\0')
        i++;

    // Vérifie si la commande commence par un pipe
    if (shell->current_line[i] == '|')
        return (2);

    // Parcourt la ligne pour détecter les guillemets non fermés
    while (shell->current_line[i] != '\0') {
        if (shell->current_line[i] == '\'' && double_quote_open == 0) {
            single_quote_open = !single_quote_open;
        } else if (shell->current_line[i] == '"' && single_quote_open == 0) {
            double_quote_open = !double_quote_open;
        }
        i++;
    }

    // Ignore les espaces à la fin de la commande
    while (len > 0 && shell->current_line[len - 1] == ' ')
        len--;

    if (len == 0)
        return (0);

    // Vérifie si la commande se termine par un pipe ou une redirection
    if (shell->current_line[len - 1] == '|')
        return (1);
    else if (shell->current_line[len - 1] == '<' || shell->current_line[len - 1] == '>')
        return (3);

    // Vérifie s'il y a des guillemets non fermés
    if (single_quote_open || double_quote_open)
        return (4);

    return (0);
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
	int		syntax_error;

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
		syntax_error = is_invalid_syntax(shell);
		if (syntax_error != 0)
		{
			if (syntax_error == 2) // Commande commence par un pipe
			{
				write(STDERR_FILENO, "minishell: syntax error near unexpected token '|'\n", 51);
				shell->exit_code = 130;
			}
			else if (syntax_error == 1) // Commande se termine par un pipe
			{
				write(STDERR_FILENO, "minishell: syntax error near unexpected token 'end of file'\n", 61);
				shell->exit_code = 130;
			}
			else if (syntax_error == 3) // Commande se termine par une redirection
			{
				write(STDERR_FILENO, "minishell: syntax error near unexpected token 'newline'\n", 56);
				shell->exit_code = 2;
			}
			else if (syntax_error == 4) // Commande contient des guillemets non fermés
			{
				write(STDERR_FILENO, "minishell: syntax error: unclosed quotes\n", 41);
				shell->exit_code = 2;
			}
			add_history(shell->current_line);
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
	free_all_shells(shell);
	free_array(env);
	return (0);
}
