/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:17:12 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/13 06:02:51 by ayarmaya         ###   ########.fr       */
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
# include <limits.h>

typedef struct s_minishell
{
	char	**envp;
	char	*current_line;
	char	**current_arg;
	char	*command_path;
	char	*current_cmd;
	char	*current_path;
	char	*target_path;
	int		exit_code;
}	t_minishell;

//Parsing
void	parse_command(t_minishell *shell);

//Exec
char	*find_command_path(t_minishell *shell);
void	execute_command(t_minishell *shell);

//Builtin
int		is_builtin(t_minishell *shell);
void	handle_builtin(t_minishell *shell);
	//Echo
void	ft_echo(t_minishell *shell);
	//Pwd
void	ft_pwd(void);
	//Env
void	ft_env(t_minishell *shell);
	//CD
void	ft_cd(t_minishell *shell);
	//Exit
void	ft_exit(t_minishell *shell);
	//Export
void	update_env(t_minishell *shell, const char *name, const char *value);
void	ft_export(t_minishell *shell);
	//Unset
void	ft_unset(t_minishell *shell);

//Signal
void	handle_sigint(int sig);
void	setup_signals(void);

//Utils main

//Utils exec
void	free_array(char **array);
void	free_args(t_minishell *shell);

#endif