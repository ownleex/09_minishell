/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:56:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/02 00:55:30 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_minishell *shell)
{
	int		i;

	i = 1;
	while (shell->current_arg[i])
	{
		if (i > 1)
			printf(" ");
		printf("%s", shell->current_arg[i]);
		i++;
	}
	printf("\n");
}
