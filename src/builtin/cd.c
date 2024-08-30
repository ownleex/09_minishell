/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:02:30 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/28 01:45:41 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **ft_cd(t_shell *shell, char **env)
{
	int		ret;
	char	*path;
	char	*oldpwd;
	char	*new_path;

	if (!shell->current_arg[1])
	{
		shell->exit_code = 1;
		return (env);
	}
	path = shell->current_arg[1];
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		shell->exit_code = 1;
		return (env);
	}
	ret = chdir(path);
	if (ret == -1)
	{
		perror("bash: cd");
		free(oldpwd);
		shell->exit_code = 1;
		return (env);
	}
	env = update_env(env, "OLDPWD", oldpwd);
	free(oldpwd);
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		perror("getcwd");
		shell->exit_code = 1;
		return (env);
	}
	env = update_env(env, "PWD", new_path);
	free(shell->current_path);
	shell->current_path = new_path;
	shell->exit_code = 0;
	return (env);
}
