/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:12:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/01 00:26:54 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	void_argc_argv(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	void_argc_argv(argc, argv);
	shell.envp = envp;
	setup_signals();
	while (1)
	{
		shell.current_line = readline("minishell$> ");
		if (shell.current_line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (strlen(shell.current_line) > 0)
		{
			add_history(shell.current_line);
			parse_command(&shell);
			execute_command(&shell);
		}
	}
	rl_clear_history();
	return (0);
}
