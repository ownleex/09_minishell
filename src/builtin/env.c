/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:11:10 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/07 14:29:21 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
		i++;
	}
}
