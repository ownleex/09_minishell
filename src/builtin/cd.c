/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:02:30 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/04 03:40:44 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_home_directory(char **env)
{
	while (*env)
	{
		if (strncmp(*env, "HOME=", 5) == 0)
			return (*env + 5);
		env++;
	}
	return (NULL);
}

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

char	*change_directory(t_shell *shell, char **env, char *path)
{
	int		ret;
	char	oldpwd[PATH_MAX];
	char	new_path[PATH_MAX];

	if (!validate_directory(shell, path))
		return (NULL);
	if (!getcwd(oldpwd, PATH_MAX))
	{
		perror("getcwd");
		shell->exit_code = 1;
		return (NULL);
	}
	ret = chdir(path);
	if (ret == -1)
	{
		perror("minishell: cd");
		shell->exit_code = 1;
		return (NULL);
	}
	env = update_env(env, "OLDPWD", oldpwd);
	if (!getcwd(new_path, PATH_MAX))
	{
		perror("getcwd");
		shell->exit_code = 1;
		return (NULL);
	}
	return (ft_strdup(new_path));
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
			return (NULL);
		}
	}
	else
		path = shell->current_arg[1];
	return (path);
}

char	**ft_cd(t_shell *shell, char **env)
{
	char	*path;
	char	*new_path;

	if (shell->current_arg[1] && shell->current_arg[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		shell->exit_code = 1;
		return (env);
	}
	path = get_cd_path(shell, env);
	if (!path)
		return (env);

	new_path = change_directory(shell, env, path);
	if (!new_path)
		return (env);

	env = update_env(env, "PWD", new_path);
	free(path);
	free(new_path);
	free(shell->current_path);
	shell->current_path = new_path;
	shell->exit_code = 0;
	return (env);
}
