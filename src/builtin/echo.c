/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 22:56:26 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/09 02:19:05 by ayarmaya         ###   ########.fr       */
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
	char	*value;

	i = 1;
	while (shell->current_arg[i])
	{
		if (i > 1)
			printf(" ");
		if (shell->current_arg[i][0] == '$' && \
		ft_strlen(shell->current_arg[i]) > 1)
		{
			value = get_env_value(shell->envp, &shell->current_arg[i][1]);
			if (value)
				printf("%s", value);
			else
				printf("%s", shell->current_arg[i]);
		}
		else
		{
			printf("%s", shell->current_arg[i]);
		}
		i++;
	}
	printf("\n");
}
