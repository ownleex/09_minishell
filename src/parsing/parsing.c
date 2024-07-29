/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:16:06 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/29 04:14:01 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_command(t_minishell *shell)
{
	shell->current_arg = ft_split(shell->current_line, ' ');
	shell->current_cmd = shell->current_arg[0];
}
