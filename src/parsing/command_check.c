/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 03:25:13 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/05 03:25:15 by ayarmaya         ###   ########.fr       */
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
		"minishell: syntax error: two chevrons with spaces between them\n", 64);
		shell->exit_code = 2;
	}
}

int	is_invalid_syntax(t_shell *shell)
{
	int len = ft_strlen(shell->current_line);
	int i = 0;
	int single_quote_open = 0;
	int double_quote_open = 0;

	// Ignore les espaces au début de la commande
	while (shell->current_line[i] == ' ' && shell->current_line[i] != '\0')
		i++;

	// Vérifie si la commande commence par un pipe
	if (shell->current_line[i] == '|')
		return (2);

	// Parcourt la ligne pour détecter les guillemets non fermés et les erreurs supplémentaires
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

		// Vérification des erreurs : deux pipes se suivent
		if (shell->current_line[i] == '|' && shell->current_line[i + 1] != '\0')
		{
			int j = i + 1;
			while (shell->current_line[j] == ' ')
				j++;
			if (shell->current_line[j] == '|')
				return (5); // Deux pipes se suivent
		}

		// Vérification des erreurs : redirection suivie d'un pipe ou pipe suivi d'une redirection
		if (shell->current_line[i] == '>' || shell->current_line[i] == '<')
		{
			int j = i + 1;
			while (shell->current_line[j] == ' ')
				j++;
			if (shell->current_line[j] == '|')
				return (6); // Redirection suivie d'un pipe
		}
		else if (shell->current_line[i] == '|')
		{
			int j = i + 1;
			while (shell->current_line[j] == ' ')
				j++;
			if (shell->current_line[j] == '>' || shell->current_line[j] == '<')
				return (7); // Pipe suivi d'une redirection
		}

		// Vérification des erreurs : deux chevrons à droite se suivent avec un ou plusieurs espaces
		if (shell->current_line[i] == '>')
		{
			int j = i + 1;
			while (shell->current_line[j] == ' ')
				j++;
			if (shell->current_line[j] == '>' && j != i + 1)
				return (8); // Deux chevrons avec des espaces entre eux
		}

		i++;
	}

	// Ignore les espaces à la fin de la commande
	while (len > 0 && shell->current_line[len - 1] == ' ')
		len--;

	if (len == 0)
		return (0);

	// Vérifie si la commande se termine par un pipe ou une redirection
	if (shell->current_line[len - 1] == '|')
		return (1);
	else if (shell->current_line[len - 1] == '<' || shell->current_line[len - 1] == '>')
		return (3);

	// Vérifie s'il y a des guillemets non fermés
	if (single_quote_open || double_quote_open)
		return (4);

	return (0);
}

