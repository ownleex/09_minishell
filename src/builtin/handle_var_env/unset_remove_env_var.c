/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 04:31:05 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/11 17:40:50 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_var_index(char **env, const char *name)
{
	int	i;
	int	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	**allocate_new_envp(int envp_size)
{
	char	**new_envp;

	new_envp = (char **)malloc(sizeof(char *) * envp_size);
	if (!new_envp)
	{
		perror("malloc");
		return (NULL);
	}
	return (new_envp);
}

char	**copy_env_except_index(char **env, int index, int envp_size)
{
	int		j;
	int		k;
	char	**new_envp;

	new_envp = allocate_new_envp(envp_size);
	if (!new_envp)
		return (env);
	j = 0;
	k = 0;
	while (env[j])
	{
		if (j != index)
		{
			new_envp[k] = env[j];
			k++;
		}
		j++;
	}
	new_envp[k] = NULL;
	return (new_envp);
}

void	ftk_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], STDOUT_FILENO);
		i++;
	}
}

char	**remove_env_var(char **env, const char *name)
{
	int		index;
	int		envp_size;
	char	**new_envp;

	index = find_env_var_index(env, name);
	if (index == -1)
		return (env);
	envp_size = 0;
	while (env[envp_size])
		envp_size++;
	new_envp = copy_env_except_index(env, index, envp_size);
	if (new_envp == env)
		return (env);
	free(env[index]);
	free(env);
	return (new_envp);
}
