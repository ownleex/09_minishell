/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:12:22 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/17 16:54:53 by ayarmaya         ###   ########.fr       */
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

void	ft_init(t_shell *shell, char **envp)
{
	int		i;
	int		envp_len;

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
	shell->target_path = NULL;
	shell->exit_code = 0;
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
	t_shell	shell;

	void_argc_argv(argc, argv);
	ft_init(&shell, envp);
	setup_signals();
	while (1)
	{
		shell.current_line = readline("minishell$> ");
		if (shell.current_line == NULL)
		{
			printf("\b exit\n");
			break ;
		}
		if (is_empty_or_whitespace(shell.current_line))
		{
			free(shell.current_line);
			continue ;
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
	free_array(shell.envp);
	return (0);
}
