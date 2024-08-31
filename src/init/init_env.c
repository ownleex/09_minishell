/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 03:02:43 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/31 03:04:36 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env_and_allocate(char **envp, int *envp_len)
{
	char	**new_envp;
	int		i;

	*envp_len = 0;
	while (envp[*envp_len])
		(*envp_len)++;
	new_envp = (char **)malloc(sizeof(char *) * (*envp_len + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < *envp_len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			perror("strdup");
			while (i > 0)
				free(new_envp[--i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

char	**init_env(char **envp)
{
	int		envp_len;
	char	**new_envp;
	char	*shlvl_str;
	int		shlvl;

	new_envp = copy_env_and_allocate(envp, &envp_len);
	if (!new_envp)
		return (NULL);
	shlvl_str = getenv("SHLVL");
	if (shlvl_str)
	{
		shlvl = ft_atoi(shlvl_str) + 1;
	}
	else
	{
		shlvl = 1;
	}
	shlvl_str = ft_itoa(shlvl);
	if (shlvl_str)
	{
		new_envp = update_env(new_envp, "SHLVL", shlvl_str);
		free(shlvl_str);
	}
	return (new_envp);
}
