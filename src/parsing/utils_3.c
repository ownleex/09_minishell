/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:34:49 by noldiane          #+#    #+#             */
/*   Updated: 2024/09/20 15:40:42 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	do_separator(char *line, int index, int *len)
{
	index = jump_arg(line, index);
	(*len)++;
	return (index);
}

int	do_pipe(int index, int *len)
{
	index++;
	(*len) += 2;
	return (index);
}

int	do_redirection(char *line, int index, int *len)
{
	if (line[index + 1] == '>')
		index += 2;
	else
		index++;
	(*len) += 2;
	return (index);
}
