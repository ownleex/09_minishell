/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:38:00 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/26 23:24:00 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**remove_env_var(char **env, const char *name)
{
	int		i;
	int		j;
	int		name_len;
	int		envp_size;
	char	**new_envp;

	name_len = ft_strlen(name);
	i = 0;
	envp_size = 0;
	while (env[envp_size])
		envp_size++;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			break ;
		i++;
	}
	if (!env[i])
		return (env);
	new_envp = (char **)malloc(sizeof(char *) * envp_size);
	if (!new_envp)
	{
		perror("malloc");
		return (env);
	}
	j = 0;
	while (env[j])
	{
		if (j != i)
		{
			if (j < i)
				new_envp[j] = env[j];
			else
				new_envp[j - 1] = env[j];
		}
		j++;
	}
	new_envp[envp_size - 1] = NULL;
	free(env[i]);
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
