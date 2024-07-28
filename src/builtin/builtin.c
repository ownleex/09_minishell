/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:59:13 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/29 00:33:34 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_minishell *shell)
{
	if (strcmp(shell->current_cmd, "echo") == 0)
		return (1);
	return (0);
}

void	handle_builtin(t_minishell *shell)
{
	if (strcmp(shell->current_cmd, "echo") == 0)
		ft_echo(shell);
}
