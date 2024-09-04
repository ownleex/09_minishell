/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:12:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/04 22:51:19 by ayarmaya         ###   ########.fr       */
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
			env = execute_command(shell, env);
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
