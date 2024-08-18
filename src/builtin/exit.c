/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:23:33 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/18 16:44:35 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell)
{
	int	exit_code;

	if (shell->current_arg[1])
		exit_code = ft_atoi(shell->current_arg[1]);
	else
		exit_code = 0;
	printf("exit\n");
	rl_clear_history();
	free_shell(shell);
	exit(exit_code);
}
