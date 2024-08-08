/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:02:30 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/08 22:20:27 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_minishell *shell)
{
	int		ret;
	char	*path;

	if (!shell->current_arg[1])
		return;
	path = shell->current_arg[1];
	ret = chdir(path);
	if (ret == -1)
	{
		perror("bash: cd");
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
