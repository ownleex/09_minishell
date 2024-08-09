/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 00:02:30 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/09 00:27:50 by ayarmaya         ###   ########.fr       */
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

void	update_env(t_minishell *shell, const char *name, const char *value)
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

void	ft_cd(t_minishell *shell)
{
	int		ret;
	char	*path;
	char	*oldpwd;
	char	*new_path;

	if (!shell->current_arg[1])
		return ;
	path = shell->current_arg[1];
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		return ;
	}
	ret = chdir(path);
	if (ret == -1)
	{
		perror("bash: cd");
		free(oldpwd);
		return ;
	}
	update_env(shell, "OLDPWD", oldpwd);
	free(oldpwd);
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		perror("getcwd");
		return ;
	}
	update_env(shell, "PWD", new_path);
	free(shell->current_path);
	shell->current_path = new_path;
}
