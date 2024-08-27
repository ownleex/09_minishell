/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:47:46 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/27 02:05:43 by ayarmaya         ###   ########.fr       */
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
	//shell->exit_code = 0;
	shell->input_file = NULL;
	shell->output_file = NULL;
	shell->append_output = 0;
	shell->pipe_in = -1;
	shell->pipe_out = -1;
	shell->is_piped = 0;
	shell->next = NULL;
	shell->instance_count = 1;
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

char	**init_env(char **envp)
{
	int		i;
	char	**new_envp;
	int		envp_len;
	char	*shlvl_str;
	int		shlvl;

	envp_len = 0;
	while (envp[envp_len])
		envp_len++;
	new_envp = (char **)malloc(sizeof(char *) * (envp_len + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < envp_len)
	{
		new_envp[i] = ft_strdup(envp[i]);
		if (!new_envp[i])
		{
			perror("strdup");
			while (i > 0)
				free(new_envp[--i]);
			free(new_envp);
			return (NULL);
		}
		i++;
	}
	new_envp[i] = NULL;
	shlvl_str = getenv("SHLVL");
	if (shlvl_str)
	{
		shlvl = ft_atoi(shlvl_str);
		shlvl++;
	}
	else
		shlvl = 1;
	shlvl_str = ft_itoa(shlvl);
	if (shlvl_str)
	{
		new_envp = update_env(new_envp, "SHLVL", shlvl_str);
		free(shlvl_str);
	}
	return (new_envp);
}


void	ft_init(t_shell *shell)
{
	ft_init_variables(shell);
	if (!ft_set_current_path(shell))
	{
		free(shell);
		return ;
	}
}
