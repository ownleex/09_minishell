/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_update_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 04:31:15 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/01 01:45:25 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_envp_size(char **envp)
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

char	*create_new_var(const char *name, const char *value)
{
	int		name_len;
	int		value_len;
	char	*new_var;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	new_var = (char *)malloc(name_len + value_len + 2);
	if (!new_var)
		return (NULL);
	ft_strlcpy(new_var, name, name_len + 1);
	ft_strlcat(new_var, "=", name_len + 2);
	ft_strlcat(new_var, value, name_len + value_len + 2);
	return (new_var);
}

char	**replace_existing_var(char **env, int index, const char *name, \
const char *value)
{
	char	*new_var;

	free(env[index]);
	new_var = create_new_var(name, value);
	if (!new_var)
		return (env);
	env[index] = new_var;
	return (env);
}

char	**append_new_var(char **env, const char *name, const char *value)
{
	char	**new_envp;
	int		envp_size;
	int		i;

	envp_size = get_envp_size(env);
	new_envp = (char **)malloc(sizeof(char *) * (envp_size + 2));
	if (!new_envp)
		return (env);
	i = -1;
	while (++i < envp_size)
		new_envp[i] = env[i];
	new_envp[envp_size] = create_new_var(name, value);
	new_envp[envp_size + 1] = NULL;
	free(env);
	return (new_envp);
}

char	**update_env(char **env, const char *name, const char *value)
{
	int		i;
	int		name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
			return (replace_existing_var(env, i, name, value));
		i++;
	}
	return (append_new_var(env, name, value));
}
