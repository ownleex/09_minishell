/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:37:37 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/13 04:37:13 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_export_no_args(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	return (env);
}

char	**ft_export(t_shell *shell, char **env)
{
	int		i;
	char	*name;
	char	*value;
	char	*equal_sign;

	if (!shell->current_arg[1])
		return (ft_export_no_args(env));
	i = 1;
	while (shell->current_arg[i])
	{
		equal_sign = ft_strchr(shell->current_arg[i], '=');
		if (equal_sign)
		{
			name = ft_substr(shell->current_arg[i], 0, \
			equal_sign - shell->current_arg[i]);
			value = ft_strdup(equal_sign + 1);
			env = update_env(env, name, value);
			free(name);
			free(value);
		}
		i++;
	}
	shell->exit_code = 0;
	return (env);
}
