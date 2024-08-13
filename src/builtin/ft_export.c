/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:37:37 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/13 04:56:53 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env(t_minishell *shell, const char *name, const char *value);

void	ft_export(t_minishell *shell)
{
	int		i;
	char	*name;
	char	*value;
	char	*equal_sign;

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
			update_env(shell, shell->current_arg[i], "");
		}
		i++;
	}
	shell->exit_code = 0;
}
