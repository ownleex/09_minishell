/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:17:12 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/07/29 02:38:23 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/ft_printf.h"
# include "../libft/include/get_next_line.h"
# include "../libft/include/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_minishell
{
	char	**envp;
	char	*current_line;
	char	**current_args;
	char	*command_path;
	char	*current_cmd;
}	t_minishell;

//Parsing
void	parse_command(t_minishell *shell);

//Builtin
int		is_builtin(t_minishell *shell);
void	handle_builtin(t_minishell *shell);
	//Echo
void	ft_echo(t_minishell *shell);

//Exec
char	*find_command_path(t_minishell *shell);
void	execute_command(t_minishell *shell);

//Signal
void	handle_sigint(int sig);
void	setup_signals(void);

//Utils
void	free_args(t_minishell *shell);
void	free_array(char **array);

#endif