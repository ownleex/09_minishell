/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:59:13 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/03 03:13:15 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_minishell *shell)
{
	if (strcmp(shell->current_cmd, "echo") == 0)
		return (1);
	else if (strcmp(shell->current_cmd, "pwd") == 0)
		return (1);
	return (0);
	//ceci est un test
}

void	handle_builtin(t_minishell *shell)
{
	if (strcmp(shell->current_cmd, "echo") == 0)
		ft_echo(shell);
	else if (strcmp(shell->current_cmd, "pwd") == 0)
		ft_pwd();
}
