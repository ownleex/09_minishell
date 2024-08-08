/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:12:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/08 03:37:00 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_minishell *shell, char **envp)
{
	shell->envp = envp;
	shell->target_path = NULL;
	shell->current_path = getcwd(NULL, 0);
	if (!shell->current_path)
	{
		perror("getcwd");
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
	t_minishell	shell;

	void_argc_argv(argc, argv);
	ft_init(&shell, envp);
	setup_signals();
	while (1)
	{
		shell.current_line = readline("minishell$> ");
		if (shell.current_line == NULL)
		{
			printf("\b\b exit\n");
			break ;
		}
		if (ft_strlen(shell.current_line) > 0)
		{
			add_history(shell.current_line);
			parse_command(&shell);
			execute_command(&shell);
		}
	}
	rl_clear_history();
	free(shell.current_path);
	return (0);
}
