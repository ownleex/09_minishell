/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:38:00 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/17 16:54:53 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(t_shell *shell, const char *name)
{
	int		i;
	int		j;
	int		name_len;
	int		envp_size;
	char	**new_envp;

	name_len = ft_strlen(name);
	i = 0;
	envp_size = 0;
	while (shell->envp[envp_size])
		envp_size++;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], name, name_len) == 0 && shell->envp[i][name_len] == '=')
			break ;
		i++;
	}
	if (!shell->envp[i])
		return ;
	new_envp = (char **)malloc(sizeof(char *) * envp_size);
	if (!new_envp)
	{
		perror("malloc");
		shell->exit_code = 1;
		return ;
	}
	j = 0;
	while (shell->envp[j])
	{
		if (j != i)
		{
			if (j < i)
				new_envp[j] = shell->envp[j];
			else
				new_envp[j - 1] = shell->envp[j];
		}
		j++;
	}
	new_envp[envp_size - 1] = NULL;
	free(shell->envp[i]);
	free(shell->envp);
	shell->envp = new_envp;
}

void	ft_unset(t_shell *shell)
{
	int	i;

	if (!shell->current_arg[1])
	{
		shell->exit_code = 0;
		return ;
	}
	i = 1;
	while (shell->current_arg[i])
	{
		remove_env_var(shell, shell->current_arg[i]);
		i++;
	}
	shell->exit_code = 0;
}
