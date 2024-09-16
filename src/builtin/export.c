/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:37:37 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/17 00:21:22 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

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
	int		exit_code;

	if (!shell->current_arg[1])
		return (ft_export_no_args(env));
	i = 1;
	exit_code = 0;
	while (shell->current_arg[i])
	{
		equal_sign = ft_strchr(shell->current_arg[i], '=');
		if (equal_sign)
		{
			name = ft_substr(shell->current_arg[i], 0, equal_sign - shell->current_arg[i]);
			value = ft_strdup(equal_sign + 1);
		}
		else
		{
			name = ft_strdup(shell->current_arg[i]);
			value = NULL;
		}
		if (!is_valid_identifier(name))
		{
			ft_putstr_fd("minishell: export: '", 2);
			ft_putstr_fd(shell->current_arg[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			exit_code = 1;
		}
		else
			env = update_env(env, name, value ? value : "");
		free(name);
		if (value)
			free(value);
		i++;
	}
	shell->exit_code = exit_code;
	return (env);
}
