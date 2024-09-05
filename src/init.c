/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 01:47:46 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/05 16:15:38 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init(t_shell *shell)
{
	shell->current_line = NULL;
	shell->current_arg = NULL;
	shell->command_path = NULL;
	shell->current_cmd = NULL;
	shell->input_file = NULL;
	shell->output_file = NULL;
	shell->append_output = 0;
	shell->pipe_in = -1;
	shell->pipe_out = -1;
	shell->is_piped = 0;
	shell->has_single_quote = 0;
	shell->is_heredoc = 0;
	shell->heredoc_delimiter = NULL;
	shell->next = NULL;
}

char	**copy_env_and_allocate(char **envp, int *envp_len)
{
	char	**new_envp;
	int		i;

	*envp_len = 0;
	while (envp[*envp_len])
		(*envp_len)++;
	new_envp = (char **)malloc(sizeof(char *) * (*envp_len + 1));
	if (!new_envp)
		return (NULL);
	i = 0;
	while (i < *envp_len)
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
	return (new_envp);
}

char	**init_env(char **envp)
{
	int		envp_len;
	char	**new_envp;
	char	*shlvl_str;
	int		shlvl;

	new_envp = copy_env_and_allocate(envp, &envp_len);
	if (!new_envp)
		return (NULL);
	shlvl_str = getenv("SHLVL");
	if (shlvl_str)
	{
		shlvl = ft_atoi(shlvl_str) + 1;
	}
	else
	{
		shlvl = 1;
	}
	shlvl_str = ft_itoa(shlvl);
	if (shlvl_str)
	{
		new_envp = update_env(new_envp, "SHLVL", shlvl_str);
		free(shlvl_str);
	}
	return (new_envp);
}

int	initialize_shell(t_shell **shell, char ***env, char **envp)
{
	*env = init_env(envp);
	if (!(*env))
	{
		perror("init_env");
		return (1);
	}
	*shell = malloc(sizeof(t_shell));
	if (!(*shell))
	{
		perror("malloc");
		free_array(*env);
		return (1);
	}
	return (0);
}
