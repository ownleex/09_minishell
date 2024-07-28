/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:12:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/28 23:27:33 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	(void)argc;
	(void)argv;
	shell.envp = envp;
	while (1)
	{
		shell.current_line = readline("minishell$> ");
		if (shell.current_line == NULL)
		{
			printf("\n");
			break ;
		}
		if (strlen(shell.current_line) > 0)
		{
			add_history(shell.current_line);
			execute_command(&shell);
		}
		free(shell.current_line);
	}
	return (0);
}
