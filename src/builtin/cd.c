/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:02:30 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/02 03:05:23 by ayarmaya         ###   ########.fr       */
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
		perror("minishell: cd");
		free(oldpwd);
		shell->exit_code = 1;
		return (NULL);
	}
	env = update_env(env, "OLDPWD", oldpwd);
	free(oldpwd);
	new_path = getcwd(NULL, 0);
	return (new_path);
}

char	*get_home_directory(char **env)
{
	while (*env)
	{
		if (ft_strcmp(*env, "HOME=") == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}

char	**ft_cd(t_shell *shell, char **env)
{
	char	*path;
	char	*new_path;

	if (!shell->current_arg[1])
	{
		path = get_home_directory(env);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			shell->exit_code = 1;
			return (env);
		}
	}
	else
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
