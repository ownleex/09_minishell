/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 20:34:28 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/03 20:35:41 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_pipes(int *pipes, int num_pipes)
{
	int	j;

	j = 0;
	while (j < num_pipes)
	{
		close(pipes[j]);
		j++;
	}
}

int	*initialize_pipes(int num_cmds)
{
	int	*pipes;
	int	i;

	pipes = malloc(sizeof(int) * 2 * (num_cmds - 1));
	i = 0;
	if (!pipes)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (i < num_cmds - 1)
	{
		if (pipe(pipes + i * 2) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (pipes);
}
