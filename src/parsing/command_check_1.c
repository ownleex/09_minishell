/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:37:13 by noldiane          #+#    #+#             */
/*   Updated: 2024/10/01 19:37:47 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_trimmed_length(char *current_line)
{
	int	len;

	len = ft_strlen(current_line);
	while (len > 0 && current_line[len - 1] == ' ')
		len--;
	return (len);
}

int	final_syntax_checks(t_shell *shell, int len, int single_quote_open, \
int double_quote_open)
{
	if (len == 0 || shell->current_line[len - 1] == '|')
		return (1);
	else if (shell->current_line[len - 1] == '<' || \
	shell->current_line[len - 1] == '>')
		return (3);
	if (single_quote_open || double_quote_open)
		return (4);
	return (0);
}

int	check_quotes_and_pipe(t_shell *shell, int *single_quote_open, \
int *double_quote_open)
{
	int	i;

	i = 0;
	while (shell->current_line[i] == ' ' && shell->current_line[i] != '\0')
		i++;
	if (shell->current_line[i] == '|')
		return (2);
	while (shell->current_line[i] != '\0')
	{
		if (shell->current_line[i] == '\'' && *double_quote_open == 0)
			*single_quote_open = !(*single_quote_open);
		else if (shell->current_line[i] == '"' && *single_quote_open == 0)
			*double_quote_open = !(*double_quote_open);
		i++;
	}
	return (0);
}

int	check_operators(t_shell *shell, int i)
{
	int	result;

	result = check_pipe_errors(shell, i);
	if (result != 0)
		return (result);
	result = check_redirection_errors(shell, i);
	if (result != 0)
		return (result);
	return (0);
}

int	is_invalid_syntax(t_shell *shell)
{
	int	len;
	int	i;
	int	single_quote_open;
	int	double_quote_open;
	int	result;

	single_quote_open = 0;
	double_quote_open = 0;
	len = get_trimmed_length(shell->current_line);
	result = check_quotes_and_pipe(shell, &single_quote_open, \
	&double_quote_open);
	if (result != 0)
		return (result);
	i = 0;
	while (shell->current_line[i] != '\0')
	{
		result = check_operators(shell, i);
		if (result != 0)
			return (result);
		i++;
	}
	result = final_syntax_checks(shell, len, single_quote_open, \
	double_quote_open);
	return (result);
}
