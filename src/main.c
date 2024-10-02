/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:12:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/02 01:36:03 by ayarmaya         ###   ########.fr       */
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

int	read_and_check_input(t_shell *shell)
{
	shell->current_line = readline("minishell$> ");
	if (!shell->current_line)
		return (0);
	if (is_empty_or_whitespace(shell->current_line))
	{
		free(shell->current_line);
		return (1);
	}
	return (2);
}

void	process_shell_loop(t_shell *shell, char ***env)
{
	int	syntax_error;
	int	input_status;

	while (1)
	{
		free_args(shell);
		free_redirections(shell);
		free_all_shells(shell->next);
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
		expand_variables_in_args(shell, *env);
		execute_command(shell, env);
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
	shell->exit_code = 0;
	process_shell_loop(shell, &env);
	rl_clear_history();
	free_all_shells(shell);
	free_array(&env);
	printf("exit\n");
	return (0);
}
