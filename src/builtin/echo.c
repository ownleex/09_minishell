/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:56:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/31 02:14:03 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **env, char *var_name)
{
	int	i;
	int	var_len;

	var_len = ft_strlen(var_name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, var_len) == 0 && \
		env[i][var_len] == '=')
			return (&env[i][var_len + 1]);
		i++;
	}
	return (NULL);
}

void	expand_and_print(char *arg, char **env)
{
	char	*str;
	char	*var_start;
	char	var_name[128];
	char	*value;

	str = arg;
	while (*str)
	{
		if (*str == '$')
		{
			var_start = str + 1;
			while (*var_start && (ft_isalnum(*var_start) || *var_start == '_'))
				var_start++;
			ft_bzero(var_name, sizeof(var_name));
			ft_strlcpy(var_name, str + 1, var_start - str);
			value = get_env_value(env, var_name);
			if (value)
				printf("%s", value);
			str = var_start;
		}
		else
		{
			printf("%c", *str++);
		}
	}
}

void	ft_echo(t_shell *shell, char **env)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (shell->current_arg[i] && \
	ft_strncmp(shell->current_arg[i], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	while (shell->current_arg[i])
	{
		if (shell->has_single_quote)
			printf("%s", shell->current_arg[i]);
		else
			expand_and_print(shell->current_arg[i], env);

		if (shell->current_arg[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	shell->exit_code = 0;
}
