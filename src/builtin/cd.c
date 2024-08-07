/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:02:30 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/07 14:30:26 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_minishell *shell)
{
	int		ret;
	char	*path;

	if (!shell->current_arg[1])
	{
		write(STDERR_FILENO, "cd: too few arguments\n", 23);
		return ;
	}
	path = shell->current_arg[1];
	ret = chdir(path);
	if (ret == -1)
	{
		perror("cd");
	}
	else
	{
		free(shell->current_path);
		shell->current_path = getcwd(NULL, 0);
		if (!shell->current_path)
		{
			perror("getcwd");
		}
	}
}
