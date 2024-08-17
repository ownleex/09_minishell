/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:17:12 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/17 16:54:53 by ayarmaya         ###   ########.fr       */
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

typedef struct s_shell
{
	char			**envp;
	char			*current_line;
	char			**current_arg;
	char			*command_path;
	char			*current_cmd;
	char			*current_path;
	char			*target_path;
	int				exit_code;
	char			*input_file;
	char			*output_file;
	int				append_output;
	int				pipe_in;
	int				pipe_out;
	int				is_piped;
	struct s_shell	*next;
}	t_shell;

//Parsing
void	parse_command(t_shell *shell);

//Exec
char	*find_command_path(t_shell *shell);
void	execute_command(t_shell *shell);

//Builtin
int		is_builtin(t_shell *shell);
void	handle_builtin(t_shell *shell);
	//Echo
void	ft_echo(t_shell *shell);
	//Pwd
void	ft_pwd(void);
	//Env
void	ft_env(t_shell *shell);
	//CD
void	ft_cd(t_shell *shell);
	//Exit
void	ft_exit(t_shell *shell);
	//Export
void	update_env(t_shell *shell, const char *name, const char *value);
void	ft_export(t_shell *shell);
	//Unset
void	ft_unset(t_shell *shell);

//Signal
void	handle_sigint(int sig);
void	setup_signals(void);

//Utils main

//Utils exec
void	free_array(char **array);
void	free_args(t_shell *shell);

#endif