/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:37:37 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/22 02:40:30 by ayarmaya         ###   ########.fr       */
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

void	update_env(t_shell *shell, const char *name, const char *value)
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
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], name, name_len) == 0 && shell->envp[i][name_len] == '=')
		{
			free(shell->envp[i]);
			new_var = (char *)malloc(name_len + value_len + 2);
			if (!new_var)
				return ;
			ft_strlcpy(new_var, name, name_len + 1);
			ft_strlcat(new_var, "=", name_len + 2);
			ft_strlcat(new_var, value, name_len + value_len + 2);
			shell->envp[i] = new_var;
			return ;
		}
		i++;
	}
	envp_size = get_envp_size(shell->envp);
	new_envp = (char **)malloc(sizeof(char *) * (envp_size + 2));
	if (!new_envp)
		return ;
	i = 0;
	while (i < envp_size)
	{
		new_envp[i] = shell->envp[i];
		i++;
	}
	new_var = (char *)malloc(name_len + value_len + 2);
	if (!new_var)
		return ;
	ft_strlcpy(new_var, name, name_len + 1);
	ft_strlcat(new_var, "=", name_len + 2);
	ft_strlcat(new_var, value, name_len + value_len + 2);
	new_envp[envp_size] = new_var;
	new_envp[envp_size + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
}

void ft_export(t_shell *shell)
{
	int		i;
	char	*name;
	char	*value;
	char	*equal_sign;
	int		exists;

	if (!shell->current_arg[1])
	{
		i = 0;
		while (shell->envp[i])
		{
			printf("declare -x %s\n", shell->envp[i]);
			i++;
		}
		shell->exit_code = 0;
		return ;
	}
	i = 1;
	while (shell->current_arg[i])
	{
		equal_sign = ft_strchr(shell->current_arg[i], '=');
		if (equal_sign)
		{
			name = ft_substr(shell->current_arg[i], 0, equal_sign - shell->current_arg[i]);
			value = ft_strdup(equal_sign + 1);
			update_env(shell, name, value);
			free(name);
			free(value);
		}
		else
		{
			exists = 0;
			name = shell->current_arg[i];
			int j = 0;
			while (shell->envp[j])
			{
				if (ft_strncmp(shell->envp[j], name, ft_strlen(name)) == 0 &&
					shell->envp[j][ft_strlen(name)] == '=')
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
}
