/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:11:05 by noldiane          #+#    #+#             */
/*   Updated: 2024/09/20 15:34:41 by noldiane         ###   ########.fr       */
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

int	jump_quote(t_shell *shell, int cursor)
{
	int		index;
	char	quote_type;

	index = cursor + 1;
	quote_type = shell->current_line[cursor];
	while (shell->current_line[index] && \
	shell->current_line[index] != quote_type)
		index++;
	if (shell->current_line[index] == quote_type)
		return (index + 1);
	return (index);
}

void	allocate_instance(t_shell *instance, int arg_count)
{
	instance->current_arg = (char **)malloc(sizeof(char *) * (arg_count + 1));
	instance->has_single_quote = (int *)malloc(sizeof(int) * (arg_count + 1));
	instance->was_quoted = (int *)malloc(sizeof(int) * (arg_count + 1));
	if (!instance->current_arg || !instance->has_single_quote
		|| !instance->was_quoted)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
}

void	handle_input_redirection(t_shell *shell, int i, t_shell *main_shell)
{
	if (shell->current_arg[i][0] == '<' && shell->current_arg[i][1] == '<')
	{
		if (main_shell->heredoc_delimiter)
			free(main_shell->heredoc_delimiter);
		main_shell->heredoc_delimiter = ft_strdup(shell->current_arg[i + 1]);
		main_shell->is_heredoc = 1;
	}
	else if (shell->current_arg[i][0] == '<')
	{
		if (main_shell->input_file)
			free(main_shell->input_file);
		main_shell->input_file = ft_strdup(shell->current_arg[i + 1]);
	}
}

void	handle_output_redirection(t_shell *shell, int i, t_shell *main_shell)
{
	int	fd;

	if (main_shell->output_file)
		free(main_shell->output_file);
	main_shell->output_file = ft_strdup(shell->current_arg[i + 1]);
	if (ft_strlen(shell->current_arg[i]) == 2)
	{
		main_shell->append_output = 1;
		fd = open(shell->current_arg[i + 1], O_WRONLY \
		| O_CREAT | O_APPEND, 0644);
	}
	else
		fd = open(shell->current_arg[i + 1], O_WRONLY \
		| O_CREAT | O_TRUNC, 0644);
	if (fd != -1)
		close(fd);
}
