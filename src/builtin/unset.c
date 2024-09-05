/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 04:38:00 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/05 04:32:14 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_unset(t_shell *shell, char **env)
{
	int	i;

	if (!shell->current_arg[1])
	{
		shell->exit_code = 0;
		return (env);
	}
	i = 1;
	while (shell->current_arg[i])
	{
		env = remove_env_var(env, shell->current_arg[i]);
		i++;
	}
	shell->exit_code = 0;
	return (env);
}
