/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:23:33 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/29 01:58:33 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell, char **env)
{
	int	exit_code;

	if (shell->current_arg[1])
		exit_code = ft_atoi(shell->current_arg[1]);
	else
		exit_code = 0;
	printf("exit\n");
	rl_clear_history();
	//free_shell(shell);
	free_all_shells(shell);
	free_array(env);
	exit(exit_code);
}
