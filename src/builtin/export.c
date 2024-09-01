/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:37:37 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/01 22:04:40 by ayarmaya         ###   ########.fr       */
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

char	**update_env(char **env, const char *name, const char *value)
{
	int		i;
	int		name_len;
	int		value_len;
	int		envp_size;
	char	*new_var;
	char	**new_envp;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			free(env[i]);
			new_var = (char *)malloc(name_len + value_len + 2);
			if (!new_var)
				return (env); // Si l'allocation échoue, retourne l'environnement inchangé
			ft_strlcpy(new_var, name, name_len + 1);
			ft_strlcat(new_var, "=", name_len + 2);
			ft_strlcat(new_var, value, name_len + value_len + 2);
			env[i] = new_var;
			return (env);
		}
		i++;
	}
	envp_size = get_envp_size(env);
	new_envp = (char **)malloc(sizeof(char *) * (envp_size + 2));
	if (!new_envp)
		return (env); // Si l'allocation échoue, retourne l'environnement inchangé
	i = 0;
	while (i < envp_size)
	{
		new_envp[i] = env[i];
		i++;
	}
	new_var = (char *)malloc(name_len + value_len + 2);
	if (!new_var)
		return (env); // Si l'allocation échoue, retourne l'environnement inchangé
	ft_strlcpy(new_var, name, name_len + 1);
	ft_strlcat(new_var, "=", name_len + 2);
	ft_strlcat(new_var, value, name_len + value_len + 2);
	new_envp[envp_size] = new_var;
	new_envp[envp_size + 1] = NULL;
	free(env);
	return (new_envp);
}

char	**ft_export(t_shell *shell, char **env)
{
	int		i;
	char	*name;
	char	*value;
	char	*equal_sign;
	int		exists;

	if (!shell->current_arg[1])
	{
		i = 0;
		while (env[i])
		{
			printf("declare -x %s\n", env[i]);
			i++;
		}
		shell->exit_code = 0;
		return (env);
	}
	i = 1;
	while (shell->current_arg[i])
	{
		equal_sign = ft_strchr(shell->current_arg[i], '=');
		if (equal_sign)
		{
			name = ft_substr(shell->current_arg[i], 0, equal_sign - shell->current_arg[i]);
			value = ft_strdup(equal_sign + 1);
			env = update_env(env, name, value);
			free(name);
			free(value);
		}
		else
		{
			exists = 0;
			name = shell->current_arg[i];
			int j = 0;
			while (env[j])
			{
				if (ft_strcmp(env[j], name) == 0 &&
					env[j][ft_strlen(name)] == '=')
				{
					exists = 1;
					break ;
				}
				j++;
			}
			if (!exists)
			{
				shell->exit_code = 0;
			}
		}
		i++;
	}
	shell->exit_code = 0;
	return (env);
}
