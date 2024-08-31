/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:38:00 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/31 02:42:16 by ayarmaya         ###   ########.fr       */
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

char	**ft_unset(t_shell *shell, char **env)
{
	int	i;

	if (!shell->current_arg[1])
	{
		shell->exit_code = 0;
		return (env);
	}
	i = 1;
	while (shell->current_arg[i])
	{
		env = remove_env_var(env, shell->current_arg[i]);
		i++;
	}
	shell->exit_code = 0;
	return (env);
}
