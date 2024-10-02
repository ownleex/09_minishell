/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:02:30 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/02 03:13:25 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_directory(t_shell *shell, char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
	{
		perror("minishell: cd");
		shell->exit_code = 1;
		return (0);
	}
	if (!S_ISDIR(path_stat.st_mode))
	{
		ft_putstr_fd("minishell: cd: not a directory\n", 2);
		shell->exit_code = 1;
		return (0);
	}
	return (1);
}

char	*change_directory(t_shell *shell, char *path)
{
	if (!validate_directory(shell, path))
		return (NULL);
	if (chdir(path) == -1)
	{
		perror("minishell: cd");
		shell->exit_code = 1;
		return (NULL);
	}
	return (getcwd(NULL, 0));
}

char	*get_cd_path(t_shell *shell, char **env)
{
	char	*path;

	if (!shell->current_arg[1])
	{
		path = get_home_directory(env);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			shell->exit_code = 1;
		}
	}
	else
		path = shell->current_arg[1];
	return (path);
}

char	**cd_change_directory(t_shell *shell, char **env, char *path)
{
	char	*new_path;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		shell->exit_code = 1;
		return (env);
	}
	new_path = change_directory(shell, path);
	if (!new_path)
	{
		free(oldpwd);
		return (env);
	}
	env = update_env(env, "OLDPWD", oldpwd);
	env = update_env(env, "PWD", new_path);
	free(oldpwd);
	free(new_path);
	shell->exit_code = 0;
	return (env);
}

char	**ft_cd(t_shell *shell, char **env)
{
	char	*path;

	if (shell->current_arg[1] && shell->current_arg[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->exit_code = 1;
		return (env);
	}
	path = get_cd_path(shell, env);
	if (!path)
		return (env);
	env = cd_change_directory(shell, env, path);
	return (env);
}
