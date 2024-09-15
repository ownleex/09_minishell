/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:56:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/15 22:33:09 by ayarmaya         ###   ########.fr       */
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

void	handle_variable_expansion(char **str_ptr, char **env, t_shell *shell)
{
	char	*str;
	char	*var_start;
	char	var_name[1024];
	char	*value;
	char	*var_end;
	int		var_len;

	str = *str_ptr;
	var_start = str + 1;
	if (*var_start == '?')
	{
		printf("%d", shell->exit_code);
		*str_ptr = var_start + 1;
		return ;
	}
	if (*var_start == '\0' || *var_start == ' ' || \
		(!ft_isalnum(*var_start) && *var_start != '_'))
	{
		printf("$");
		*str_ptr = var_start;
		return ;
	}
	var_end = var_start;
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	var_len = var_end - var_start;
	ft_bzero(var_name, sizeof(var_name));
	ft_strlcpy(var_name, var_start, var_len + 1);
	value = get_env_value(env, var_name);
	if (value)
		printf("%s", value);
	*str_ptr = var_end;
}

void	expand_and_print(char *arg, char **env, t_shell *shell)
{
	char	*str;

	str = arg;
	while (*str)
	{
		if (*str == '$')
			handle_variable_expansion(&str, env, shell);
		else
		{
			printf("%c", *str);
			str++;
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
			expand_and_print(shell->current_arg[i], env, shell);
		if (shell->current_arg[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	shell->exit_code = 0;
}
