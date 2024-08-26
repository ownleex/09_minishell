/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:17:12 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/08/26 23:17:51 by ayarmaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
	int				instance_count;
	struct s_shell	*next;
}	t_shell;

// Environment management
char	**init_env(char **envp);
char	**update_env(char **env, const char *name, const char *value);
char	**remove_env_var(char **env, const char *name);;

// Parsing
void	handle_cmd(t_shell *shell);
void	count_instance(t_shell *shell);
void	parse_command(t_shell *shell);

// Exec
char	*find_command_path(t_shell *shell, char **env);
void	execute_command(t_shell *shell, char **env);

// Builtin
int		is_builtin(t_shell *shell);
char	**handle_builtin(t_shell *shell, char **env);
	// Echo
void	ft_echo(t_shell *shell, char **env);
	// Pwd
void	ft_pwd(void);
	// Env
void	ft_env(t_shell *shell, char **env);
	// CD
void	ft_cd(t_shell *shell, char **env);
	// Exit
void	ft_exit(t_shell *shell);
	// Export
char	**ft_export(t_shell *shell, char **env);
	// Unset
char	**ft_unset(t_shell *shell, char **env);

// Signal
void	handle_sigint(int sig);
void	setup_signals(void);

// Utils main
void	free_shell(t_shell *shell);
void	free_all_shells(t_shell *shell);
void	ft_init(t_shell *shell, char **env);

// Utils exec
void	free_array(char **array);
void	free_args(t_shell *shell);

// Init
void	ft_init(t_shell *shell, char **env);

#endif
