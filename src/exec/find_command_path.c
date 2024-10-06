/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 23:58:37 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/06 17:16:46 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*search_command_in_path(char *cmd, char **path_split)
{
	char	*full_path;
	char	*temp;
	int		i;

	i = 0;
	while (path_split[i])
	{
		full_path = ft_strjoin(path_split[i], "/");
		temp = full_path;
		full_path = ft_strjoin(full_path, cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			free_array(&path_split);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(&path_split);
	return (NULL);
}

char	*get_path_from_env(char **env)
{
	char	**path_split;
	char	*path;
	int		i;

	i = 0;
	while (env[i])
	{
		path_split = ft_split(env[i], '=');
		if (ft_strcmp(path_split[0], "PATH") == 0)
		{
			path = ft_strdup(path_split[1]);
			free_array(&path_split);
			return (path);
		}
		free_array(&path_split);
		i++;
	}
	return (NULL);
}

char	*find_command_path(t_shell *shell, char **env)
{
	char	*path;
	char	**path_split;

	if (ft_strchr(shell->current_cmd, '/'))
	{
		if (access(shell->current_cmd, X_OK) == 0)
			return (ft_strdup(shell->current_cmd));
		else
			return (NULL);
	}
	path = get_path_from_env(env);
	if (!path)
		return (NULL);
	path_split = ft_split(path, ':');
	free(path);
	return (search_command_in_path(shell->current_cmd, path_split));
}
