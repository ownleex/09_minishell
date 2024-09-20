/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_check_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 18:50:51 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/20 18:51:42 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error_and_exit(t_shell *shell, int exit_code, char *error_msg)
{
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	shell->exit_code = exit_code;
}

void	handle_syntax_error(t_shell *shell, int syntax_error)
{
	if (syntax_error == 2)
		print_error_and_exit(shell, 130, \
		"minishell: syntax error near unexpected token '|'\n");
	else if (syntax_error == 1)
		print_error_and_exit(shell, 130, \
		"minishell: syntax error near unexpected token 'end of file'\n");
	else if (syntax_error == 3)
		print_error_and_exit(shell, 2, \
		"minishell: syntax error near unexpected token 'newline'\n");
	else if (syntax_error == 4)
		print_error_and_exit(shell, 2, \
		"minishell: syntax error: unclosed quotes\n");
	else if (syntax_error == 5)
		print_error_and_exit(shell, 2, \
		"minishell: syntax error: two pipes in a row\n");
	else if (syntax_error == 6)
		print_error_and_exit(shell, 2, \
		"minishell: syntax error: redirection followed by a pipe\n");
	else if (syntax_error == 7)
		print_error_and_exit(shell, 2, \
		"minishell: syntax error: pipe followed by a redirection\n");
	else if (syntax_error == 8)
		print_error_and_exit(shell, 2, \
		"minishell: syntax error: syntax error near unexpected token `>'\n");
}
