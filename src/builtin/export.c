/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:37:37 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/29 22:40:09 by ayarmaya         ###   ########.fr       */
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

void	parse_name_value(char *arg, char **name_ptr, char **value_ptr)
{
	char	*equal_sign;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
	{
		*name_ptr = ft_substr(arg, 0, equal_sign - arg);
		*value_ptr = ft_strdup(equal_sign + 1);
	}
	else
	{
		*name_ptr = ft_strdup(arg);
		*value_ptr = NULL;
	}
}

int	process_export_arg(char ***env_ptr, char *arg)
{
	char	*name;
	char	*value;
	int		exit_code;

	exit_code = 0;
	parse_name_value(arg, &name, &value);
	if (!is_valid_identifier(name))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		exit_code = 1;
	}
	else
	{
		if (value != NULL)
			*env_ptr = update_env(*env_ptr, name, value);
	}
	free(name);
	free(value);
	return (exit_code);
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
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	if (!shell->current_arg[1])
		return (ft_export_no_args(env));
	while (shell->current_arg[i])
	{
		exit_code |= process_export_arg(&env, shell->current_arg[i]);
		i++;
	}
	shell->exit_code = exit_code;
	return (env);
}
