/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:16:06 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/02 00:55:18 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_command(t_minishell *shell)
{
	shell->current_arg = ft_split(shell->current_line, ' ');
	shell->current_cmd = shell->current_arg[0];
}
