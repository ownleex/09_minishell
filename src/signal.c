/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 01:44:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/05 00:44:35 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signaled_status(t_shell *shell, int status)
{
	if (WTERMSIG(status) == SIGQUIT)
	{
		write(STDOUT_FILENO, "Quit\n", 6);
		shell->exit_code = 128 + WTERMSIG(status);
	}
	else if (WTERMSIG(status) == SIGINT)
	{
		write(STDOUT_FILENO, "\r", 1);
		shell->exit_code = 130;
	}
}

void	handle_sigquit(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(STDOUT_FILENO, "\r\n", 2);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
