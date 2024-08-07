/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:02:30 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/07 22:51:47 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_minishell *shell)
{
	int		ret;
	char	*path;

	if (!shell->current_arg[1] || strcmp(shell->current_arg[1], "~") == 0)
	{
		path = getenv("HOME");
		if (!path)
		{
			write(STDERR_FILENO, "cd: HOME not set\n", 17);
			return ;
		}
	}
	else
	{
		path = shell->current_arg[1];
	}
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
