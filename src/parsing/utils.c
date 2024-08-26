/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 11:38:10 by noldiane          #+#    #+#             */
/*   Updated: 2024/08/26 17:27:43 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirecion(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len > 2)
		return (0);
	if (str[0] != '<' && str[0] != '>')
		return (0);
	if (len == 1)
		return (1);
	else if (str[0] == str[1])
		return (1);
	return (0);
}

void	count_instance(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->next)
	{
		shell = shell->next;
		i++;
	}
	printf("There is %d minishell instances\n", i);
}

int	find_end(t_shell *shell, int start)
{
	int	i;

	i = start + 1;
	while (shell->current_arg[i])
	{
		if (shell->current_arg[i][0] == '|' || is_redirecion(shell->current_arg[i]))
			break;
		i++;
	}
	return (i);
}

void	complete_instance(t_shell *shell, t_shell *instance, int start, int end)
{
	int	i;
	int	d;

	d = 0;
	i = start + 1;
	instance->current_arg = (char **)malloc(sizeof(char *) * ((end - start)));
	while (i < end && shell->current_arg[i])
	{
		instance->current_arg[d] = ft_strdup(shell->current_arg[i]);
		i++;
		d++;
	}
	instance->current_arg[d] = NULL;
	instance->current_cmd = instance->current_arg[0];
}

void	free_main_shell(t_shell *shell)
{
	int	i;
	int	b;

	if (shell == NULL || shell->current_arg == NULL)
		return ;
	i = 0;
	while (shell->current_arg[i] != NULL)
	{
		if ((shell->current_arg[i][0] == '|' && shell->current_arg[i + 1] != NULL) || (is_redirecion(shell->current_arg[i]) && shell->current_arg[i + 1] != NULL))
		{
			b = i;
			while (shell->current_arg[b] != NULL)
			{
				free(shell->current_arg[b]);
				b++;
			}
			shell->current_arg[i] = NULL;
			return;
		}
		i++;
	}
}

void	handle_cmd(t_shell *shell)
{
	int	i;
	int	c;
	int pipe_fds[2];
	t_shell	*main_shell;

	i = 0;
	c = 1;
	main_shell = shell;
	while (shell->current_arg[i])
	{
		if (shell->current_arg[i][0] == '|' && shell->current_arg[i + 1])
		{
			main_shell->next = malloc(sizeof(t_shell));
			if (!main_shell->next)
				return;
			ft_init(main_shell->next, shell->envp);
			complete_instance(shell, main_shell->next, i, find_end(shell, i));
			if (pipe(pipe_fds) == -1)
			{
				perror("pipe");
				return;
			}
			main_shell->is_piped = 1;
			main_shell->pipe_out = pipe_fds[1];
			main_shell->next->pipe_in = pipe_fds[0];
			main_shell = main_shell->next;
			i++;
			c++;
			main_shell->instance_count = c;
		}
		else if (is_redirecion(shell->current_arg[i]) && shell->current_arg[i + 1])
		{
			main_shell->next = malloc(sizeof(t_shell));
			if (!main_shell->next)
				return;
			ft_init(main_shell->next, shell->envp);
			complete_instance(shell, main_shell->next, i, find_end(shell, i));
			if (shell->current_arg[i][0] == '<')
				main_shell->input_file = ft_strdup(shell->current_arg[i + 1]);
			else if (shell->current_arg[i][0] == '>')
				main_shell->output_file = ft_strdup(shell->current_arg[i + 1]);
			if (ft_strlen(shell->current_arg[i]) == 2)
				main_shell->append_output = 1;
			main_shell = main_shell->next;
			c++;
			main_shell->instance_count = c;
		}
		i++;
	}
	free_main_shell(shell);
}
