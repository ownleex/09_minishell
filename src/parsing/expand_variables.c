/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 01:22:02 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/02 02:06:38 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// variable_expansion.c

#include "minishell.h"

static char	*get_env_valuee(char **env, char *var_name)
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

static char	*get_env_var_value(char *str, char **env, int *i, t_shell *shell)
{
	char	var_name[256];
	int		j;
	char	*env_value;

	j = 0;
	if (str[*i] == '?')
	{
		(*i)++;
		env_value = ft_itoa(shell->exit_code);
		return (env_value);
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		var_name[j++] = str[(*i)++];
	}
	var_name[j] = '\0';
	env_value = get_env_valuee(env, var_name);
	if (env_value)
		return (ft_strdup(env_value));
	else
		return (ft_strdup(""));
}

char	*expand_variabless(char *str, char **env, t_shell *shell)
{
	char	*result;
	int		i;
	int		j;
	char	*env_value;

	result = malloc(4096);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			i++;
			env_value = get_env_var_value(str, env, &i, shell);
			if (env_value)
			{
				j += ft_strlcpy(&result[j], env_value, 4096 - j);
				free(env_value);
			}
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void	expand_variables_in_args(t_shell *shell, char **env)
{
	int		i;
	char	*expanded_arg;

	i = 1;
	while (shell->current_arg[i])
	{
		if (!shell->has_single_quote[i])
		{
			expanded_arg = expand_variabless(shell->current_arg[i], env, shell);
			if (expanded_arg)
			{
				free(shell->current_arg[i]);
				shell->current_arg[i] = expanded_arg;
			}
		}
		i++;
	}
}
