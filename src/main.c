/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:12:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/05 03:18:26 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	handle_syntax_error(t_shell *shell, int syntax_error)
{
	if (syntax_error == 2)
	{
		write(STDERR_FILENO, \
		"minishell: syntax error near unexpected token '|'\n", 51);
		shell->exit_code = 130;
	}
	else if (syntax_error == 1)
	{
		write(STDERR_FILENO, \
		"minishell: syntax error near unexpected token 'end of file'\n", 61);
		shell->exit_code = 130;
	}
	else if (syntax_error == 3)
	{
		write(STDERR_FILENO, \
		"minishell: syntax error near unexpected token 'newline'\n", 56);
		shell->exit_code = 2;
	}
	else if (syntax_error == 4)
	{
		write(STDERR_FILENO, "minishell: syntax error: unclosed quotes\n", 41);
		shell->exit_code = 2;
	}
	else if (syntax_error == 5)
	{
		write(STDERR_FILENO, "minishell: syntax error: two pipes in a row\n", 45);
		shell->exit_code = 2;
	}
	else if (syntax_error == 6)
	{
		write(STDERR_FILENO, \
		"minishell: syntax error: redirection followed by a pipe\n", 57);
		shell->exit_code = 2;
	}
	else if (syntax_error == 7)
	{
		write(STDERR_FILENO, \
		"minishell: syntax error: pipe followed by a redirection\n", 57);
		shell->exit_code = 2;
	}
	else if (syntax_error == 8)
	{
		write(STDERR_FILENO, \
		"minishell: syntax error: two chevrons with spaces between them\n", 64);
		shell->exit_code = 2;
	}
}


int	read_and_check_input(t_shell *shell)
{
	shell->current_line = readline("minishell$> ");
	if (!shell->current_line)
	{
		printf("\b exit\n");
		return (0);
	}
	if (is_empty_or_whitespace(shell->current_line))
	{
		free(shell->current_line);
		return (1);
	}
	return (2);
}

void	process_shell_loop(t_shell *shell, char **env)
{
	int	syntax_error;
	int	input_status;

	shell->exit_code = 0;
	while (1)
	{
		ft_init(shell);
		input_status = read_and_check_input(shell);
		if (input_status == 0)
			break ;
		else if (input_status == 1)
			continue ;
		syntax_error = is_invalid_syntax(shell);
		if (syntax_error != 0)
		{
			handle_syntax_error(shell, syntax_error);
			add_history(shell->current_line);
			free(shell->current_line);
			continue ;
		}
		add_history(shell->current_line);
		parse_command(shell);
		env = execute_command(shell, env);
		free_all_shells(shell->next);
		free(shell->current_line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	**env;

	if (initialize_shell(&shell, &env, envp) != 0)
		return (1);
	void_argc_argv(argc, argv);
	setup_signals();
	process_shell_loop(shell, env);
	rl_clear_history();
	free_all_shells(shell);
	free_array(env);
	return (0);
}
