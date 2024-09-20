/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: noldiane <noldiane@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:37:13 by noldiane          #+#    #+#             */
/*   Updated: 2024/09/20 15:51:48 by noldiane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_syntax_error(t_shell *shell, int syntax_error)
{
	if (syntax_error == 2)
	{
		write(STDERR_FILENO, \
		"minishell: syntax error near unexpected token '|'\n", 51);
		shell->exit_code = 130;
	}
	else if (syntax_error == 1)
	{
		write(STDERR_FILENO, \
		"minishell: syntax error near unexpected token 'end of file'\n", 61);
		shell->exit_code = 130;
	}
	else if (syntax_error == 3)
	{
		write(STDERR_FILENO, \
		"minishell: syntax error near unexpected token 'newline'\n", 56);
		shell->exit_code = 2;
	}
	else if (syntax_error == 4)
	{
		write(STDERR_FILENO, "minishell: syntax error: unclosed quotes\n", 41);
		shell->exit_code = 2;
	}
	else if (syntax_error == 5)
	{
		write(STDERR_FILENO, \
		"minishell: syntax error: two pipes in a row\n", 45);
		shell->exit_code = 2;
	}
	else if (syntax_error == 6)
	{
		write(STDERR_FILENO, \
		"minishell: syntax error: redirection followed by a pipe\n", 57);
		shell->exit_code = 2;
	}
	else if (syntax_error == 7)
	{
		write(STDERR_FILENO, \
		"minishell: syntax error: pipe followed by a redirection\n", 57);
		shell->exit_code = 2;
	}
	else if (syntax_error == 8)
	{
		write(STDERR_FILENO, \
		"minishell: syntax error: syntax error near unexpected token `>'\n", 65);
		shell->exit_code = 2;
	}
}

int	is_invalid_syntax(t_shell *shell)
{
	int len;
	int i;
	int single_quote_open;
	int double_quote_open;

	i = 0;
	single_quote_open = 0;
	double_quote_open = 0;
	len = ft_strlen(shell->current_line);
	while (shell->current_line[i] == ' ' && shell->current_line[i] != '\0')
		i++;
	if (shell->current_line[i] == '|')
		return (2);
	while (shell->current_line[i] != '\0')
	{
		if (shell->current_line[i] == '\'' && double_quote_open == 0)
		{
			single_quote_open = !single_quote_open;
		}
		else if (shell->current_line[i] == '"' && single_quote_open == 0)
		{
			double_quote_open = !double_quote_open;
		}
		else if (!single_quote_open && !double_quote_open)
		{
			if (shell->current_line[i] == '|' && shell->current_line[i + 1] != '\0')
			{
				int j = i + 1;
				while (shell->current_line[j] == ' ')
					j++;
				if (shell->current_line[j] == '|')
					return (5);
			}
			if (shell->current_line[i] == '>' || shell->current_line[i] == '<')
			{
				int j = i + 1;
				while (shell->current_line[j] == ' ')
					j++;
				if (shell->current_line[j] == '|')
					return (6);
			}
			else if (shell->current_line[i] == '|')
			{
				int j = i + 1;
				while (shell->current_line[j] == ' ')
					j++;
				if (shell->current_line[j] == '>' || shell->current_line[j] == '<')
					return (7);
			}
			if (shell->current_line[i] == '>')
			{
				int j = i + 1;
				while (shell->current_line[j] == ' ')
					j++;
				if (shell->current_line[j] == '>' && j != i + 1)
					return (8);
			}
		}
		i++;
	}
	while (len > 0 && shell->current_line[len - 1] == ' ')
		len--;
	if (len == 0)
		return (0);
	if (shell->current_line[len - 1] == '|')
		return (1);
	else if (shell->current_line[len - 1] == '<' || shell->current_line[len - 1] == '>')
		return (3);
	if (single_quote_open || double_quote_open)
		return (4);
	return (0);
}
