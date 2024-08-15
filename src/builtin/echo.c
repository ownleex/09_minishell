/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:56:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/15 22:34:21 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char **envp, char *var_name)
{
	int		i;
	int		var_len;

	var_len = ft_strlen(var_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, var_len) == 0 && \
		envp[i][var_len] == '=')
			return (&envp[i][var_len + 1]);
		i++;
	}
	return (NULL);
}

void	ft_echo(t_minishell *shell)
{
	int		i;
	int		newline;
	char	*value;

	i = 1;
	newline = 1;
	if (shell->current_arg[i] && ft_strncmp(shell->current_arg[i], "-n", 3) == 0)
	{
		newline = 0;
		i++;
	}
	while (shell->current_arg[i])
	{
		if (ft_strncmp(shell->current_arg[i], "$?", 3) == 0)
		{
			printf("%d", shell->exit_code);
		}
		else if (shell->current_arg[i][0] == '$' && ft_strlen(shell->current_arg[i]) > 1)
		{
			value = get_env_value(shell->envp, &shell->current_arg[i][1]);
			if (value)
			{
				printf("%s", value);
			}
			else
			{
				printf("\n");
				shell->exit_code = 0;
				return ;
			}
		}
		else
		{
			printf("%s", shell->current_arg[i]);
		}
		if (shell->current_arg[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	shell->exit_code = 0;
}
