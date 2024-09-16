/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instances.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:55:57 by noldiane          #+#    #+#             */
/*   Updated: 2024/09/16 22:06:20 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    complete_instance(t_shell *shell, t_shell *instance, int start, int end)
{
    int i;
    int d;

    d = 0;
    i = start + 1;
    instance->current_arg = (char **)malloc(sizeof(char *) * (end - start + 1)); // +1 pour le NULL final
    if (!instance->current_arg)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    while (i < end && shell->current_arg[i])
    {
        instance->current_arg[d] = ft_strdup(shell->current_arg[i]);
        i++;
        d++;
    }
    instance->current_arg[d] = NULL;
    instance->current_cmd = instance->current_arg[0];
}


void	handle_pipes(t_shell *shell, int *i, t_shell **main_shell, int *c)
{
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
	{
		perror("pipe");
		return ;
	}
	(*main_shell)->next = malloc(sizeof(t_shell));
	if (!(*main_shell)->next)
		return ;
	ft_init((*main_shell)->next);
	complete_instance(shell, (*main_shell)->next, *i, find_end(shell, *i));
	(*main_shell)->is_piped = 1;
	(*main_shell)->pipe_out = pipe_fds[1];
	(*main_shell)->next->pipe_in = pipe_fds[0];
	*main_shell = (*main_shell)->next;
	//(*i)++;
	(*c)++;
}

void	handle_redirections(t_shell *shell, int i, t_shell *main_shell)
{
	int	fd;

	if (shell->current_arg[i][0] == '<' && shell->current_arg[i][1] == '<')
	{
		main_shell->heredoc_delimiter = ft_strdup(shell->current_arg[i + 1]);
		main_shell->is_heredoc = 1;
	}
	else if (shell->current_arg[i][0] == '<')
		main_shell->input_file = ft_strdup(shell->current_arg[i + 1]);
	else if (shell->current_arg[i][0] == '>')
	{
		main_shell->output_file = ft_strdup(shell->current_arg[i + 1]);
		if (ft_strlen(shell->current_arg[i]) == 2)
		{
			main_shell->append_output = 1;
			fd = open(shell->current_arg[i + 1], O_WRONLY | \
			O_CREAT | O_APPEND, 0644);
		}
		else
			fd = open(shell->current_arg[i + 1], O_WRONLY | \
			O_CREAT | O_TRUNC, 0644);
		if (fd != -1)
			close(fd);
	}
}

// Dans le fichier ../../src/parsing/instances.c

void	handle_cmd(t_shell *shell)
{
    int     i;
    int     c;
    t_shell *main_shell;

    i = 0;
    c = 1;
    main_shell = shell;
    while (shell->current_arg[i])
    {
        // Vérification si le symbole de pipe n'est pas entre guillemets
        if (shell->current_arg[i][0] == '|' && shell->current_arg[i + 1] && shell->was_quoted[i] == 0)
        {
            handle_pipes(shell, &i, &main_shell, &c);
            i++;
        }
        else if (is_redirecion(shell->current_arg[i]) && shell->current_arg[i + 1] && shell->was_quoted[i] == 0)
        {
            handle_redirections(shell, i, main_shell);
            i += 2;
        }
        else
            i++;
    }
    free_main_shell(shell);
}
