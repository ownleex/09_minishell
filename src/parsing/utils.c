/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:38:10 by noldiane          #+#    #+#             */
/*   Updated: 2024/08/21 12:16:05 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirecion(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 2)
		return (0);
	if (str[0] != '<' && str[0] != '>')
		return (0);
	if (len == 1)
		return (1);
	else if (str[0] == str[1])
		return (1);
	return (0);
}

void	count_instance(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->next)
	{
		shell = shell->next;
		i++;
	}
	printf("There is %d minishell instances\n", i);
}

void	handle_cmd(t_shell *shell)
{
	int	i;
	int pipe_fds[2];
	t_shell	*main_shell;

	i = 0;
	main_shell = shell;
	while (shell->current_arg[i])
	{
		if (shell->current_arg[i][0] == '|' && shell->current_arg[i + 1])
		{
			main_shell->next = malloc(sizeof(t_shell));
			if (!main_shell->next)
				return;
			ft_init(main_shell->next, shell->envp);
			if (pipe(pipe_fds) == -1)
			{
				perror("pipe");
				return;
			}
			main_shell->is_piped = 1;
			main_shell->pipe_out = pipe_fds[1];
			main_shell->next->pipe_in = pipe_fds[0];
			main_shell = main_shell->next;
			i++;
		}
		else if (is_redirecion(shell->current_arg[i]) && shell->current_arg[i + 1])
		{
			main_shell->next = malloc(sizeof(t_shell));
			if (!main_shell->next)
				return;
			ft_init(main_shell->next, shell->envp);
			if (shell->current_arg[i][0] == '<')
				main_shell->input_file = ft_strdup(shell->current_arg[i + 1]);
			else if (shell->current_arg[i][0] == '>')
				main_shell->output_file = ft_strdup(shell->current_arg[i + 1]);
			if (ft_strlen(shell->current_arg[i]))
				main_shell->append_output = 1;
			main_shell = main_shell->next;
		}
		i++;
	}
	count_instance(shell);
}
