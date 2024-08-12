/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:59:13 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/12 20:16:31 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_minishell *shell)
{
	if (ft_strncmp(shell->current_cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

void	handle_builtin(t_minishell *shell)
{
	if (ft_strncmp(shell->current_cmd, "echo", 4) == 0)
		ft_echo(shell);
	else if (ft_strncmp(shell->current_cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(shell->current_cmd, "env", 3) == 0)
		ft_env(shell);
	else if (ft_strncmp(shell->current_cmd, "cd", 2) == 0)
		ft_cd(shell);
	else if (ft_strncmp(shell->current_cmd, "exit", 4) == 0)
		ft_exit(shell);
}
