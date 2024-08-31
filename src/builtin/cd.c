/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:02:30 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/31 02:19:14 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_directory(t_shell *shell, char **env, char *path)
{
	int		ret;
	char	*oldpwd;
	char	*new_path;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		shell->exit_code = 1;
		return (NULL);
	}
	ret = chdir(path);
	if (ret == -1)
	{
		perror("bash: cd");
		free(oldpwd);
		shell->exit_code = 1;
		return (NULL);
	}
	env = update_env(env, "OLDPWD", oldpwd);
	free(oldpwd);
	new_path = getcwd(NULL, 0);
	return (new_path);
}

char	**ft_cd(t_shell *shell, char **env)
{
	char	*path;
	char	*new_path;

	if (!shell->current_arg[1])
	{
		shell->exit_code = 1;
		return (env);
	}
	path = shell->current_arg[1];
	new_path = change_directory(shell, env, path);
	if (!new_path)
		return (env);
	env = update_env(env, "PWD", new_path);
	free(shell->current_path);
	shell->current_path = new_path;
	shell->exit_code = 0;
	return (env);
}
