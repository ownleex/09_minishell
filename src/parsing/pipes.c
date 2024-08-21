/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 16:14:25 by noldiane          #+#    #+#             */
/*   Updated: 2024/08/21 12:13:58 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipes(t_shell *shell)
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
		i++;
	}
}
