/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:47:46 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/23 13:35:31 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_variables(t_shell *shell)
{
	shell->current_line = NULL;
	shell->current_arg = NULL;
	shell->command_path = NULL;
	shell->current_cmd = NULL;
	shell->current_path = NULL;
	shell->target_path = NULL;
	shell->exit_code = 0;
	shell->input_file = NULL;
	shell->output_file = NULL;
	shell->append_output = 0;
	shell->pipe_in = -1;
	shell->pipe_out = -1;
	shell->is_piped = 0;
	shell->next = NULL;
	shell->instance_count = 1;
}

int	ft_set_env(t_shell *shell, char **envp)
{
	int		i;
	int		envp_len;

	envp_len = 0;
	while (envp[envp_len])
		envp_len++;
	shell->envp = (char **)malloc(sizeof(char *) * (envp_len + 1));
	i = 0;
	while (i < envp_len)
	{
		shell->envp[i] = ft_strdup(envp[i]);
		if (!shell->envp[i])
		{
			perror("strdup");
			while (i > 0)
				free(shell->envp[--i]);
			free(shell->envp);
			return (0);
		}
		i++;
	}
	shell->envp[i] = NULL;
	return (1);
}

int	ft_set_current_path(t_shell *shell)
{
	shell->current_path = getcwd(NULL, 0);
	if (!shell->current_path)
	{
		perror("getcwd");
		return (0);
	}
	return (1);
}

void	ft_init(t_shell *shell, char **envp)
{
	int	i;

	i = 0;
	ft_init_variables(shell);
	if (!ft_set_env(shell, envp))
	{
		free(shell);
		return ;
	}
	if (!ft_set_current_path(shell))
	{
		while (shell->envp[i])
			free(shell->envp[i++]);
		free(shell->envp);
		free(shell);
		return ;
	}
}
