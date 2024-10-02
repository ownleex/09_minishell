/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:29:42 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/02 03:08:08 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
char	*get_env_var_value(char *str, char **env, int *i, t_shell *shell)
{
	char	var_name[256];
	int		j;

	j = 0;
	(*i)++;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		var_name[j++] = str[(*i)++];
	var_name[j] = '\0';
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(shell->exit_code));
	return (get_env_value(env, var_name));
}

char	*expand_variables(char *str, char **env, t_shell *shell)
{
	char	*result;
	int		i;
	int		j;
	char	*env_value;

	result = malloc(1024);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
		{
			env_value = get_env_var_value(str, env, &i, shell);
			if (env_value)
				j += ft_strlcpy(&result[j], env_value, 1024 - j);
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}*/

char	*get_home_directory(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "HOME=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}
/*
char	*expand_argument(char *arg, char **env, t_shell *shell)
{
	if (arg == NULL)
		return (NULL);
	if (shell->current_arg[1] && shell->has_single_quote[1])
		return (ft_strdup(arg));
	return (expand_variables(arg, env, shell));
}*/
