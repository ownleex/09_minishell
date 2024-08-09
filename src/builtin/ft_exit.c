/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 18:23:33 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/09 02:23:02 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_minishell *shell)
{
	int	exit_code;

	if (shell->current_arg[1])
		exit_code = ft_atoi(shell->current_arg[1]);
	else
		exit_code = 0;
	free(shell->current_path);
	free_args(shell);
	rl_clear_history();
	printf("exit\n");
	free_array(shell->envp);
	exit(exit_code);
}
