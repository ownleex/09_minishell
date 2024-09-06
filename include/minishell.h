/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:17:12 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/09/06 21:37:39 by ayarmaya         ###   ########.fr       */
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
# include <sys/stat.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>

typedef struct s_shell
{
	char			*heredoc_delimiter;
	int				is_heredoc;
	char			*current_line;
	char			**current_arg;
	char			*command_path;
	char			*current_cmd;
	int				exit_code;
	char			*input_file;
	char			*output_file;
	int				append_output;
	int				pipe_in;
	int				pipe_out;
	int				is_piped;
	int				has_single_quote;
	struct s_shell	*next;
}	t_shell;

// Utils main
void	free_shell(t_shell *shell);
void	free_all_shells(t_shell *shell);
void	void_argc_argv(int argc, char **argv);

// Init
char	**init_env(char **envp);
void	ft_init(t_shell *shell);
int		initialize_shell(t_shell **shell, char ***env, char **envp);

// Signal
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	handle_signaled_status(t_shell *shell, int status);
void	setup_signals(void);

// Parsing
void	handle_cmd(t_shell *shell);
void	parse_command(t_shell *shell);
	// Command_check
int		is_invalid_syntax(t_shell *shell);
void	handle_syntax_error(t_shell *shell, int syntax_error);
	// Utils
int		is_quote(int c);
int		is_redirecion(char *str);
int		is_single_pipe(char *line, int p);
int		is_single_redirection(char *line, int p);
int		is_separator(int character, int space);
void	copy_inner_content(char *dest, char *src, int start, int end);
	// Arguments
int		count_args(char *line);
int		jump_arg(char *line, int cursor);
int		get_arglen(t_shell *shell, int start, int end);
void	set_arg(t_shell *shell, int start, int end, int pos);
	// Addons
void	free_main_shell(t_shell *shell);
int		find_end(t_shell *shell, int start);

// Exec
char	*find_command_path(t_shell *shell, char **env);
void	execute_command_or_builtin(t_shell *shell, char **env, pid_t *pids);
char	**execute_command(t_shell *shell, char **env);
	//Redirection_and_pipe
void	handle_redir(t_shell *shell);
void	handle_pipes_if_needed(t_shell *shell);
	//fork_and_process
void	handle_fork(t_shell *shell, char **env, pid_t *pids, int index);
void	handle_parent_process(t_shell *shell);
	//Find_command_path
char	*find_command_path(t_shell *shell, char **env);
	//heredoc
void	handle_heredoc(t_shell *shell);
void	handle_heredoc_if_needed(t_shell *shell);
	// Utils exec
void	free_array(char **array);
void	free_args(t_shell *shell);

// Builtin
int		is_builtin(t_shell *shell);
char	**handle_builtin(t_shell *shell, char **env, pid_t *pids);
	// Echo
void	ft_echo(t_shell *shell, char **env);
	// Pwd
void	ft_pwd(t_shell *shell);
	// Env
void	ft_env(t_shell *shell, char **env);
	// Exit
void	ft_exit(t_shell *shell, char **env, pid_t *pids);
	// CD
char	**ft_cd(t_shell *shell, char **env);
	// Export
char	**ft_export(t_shell *shell, char **env);
	// Unset
char	**ft_unset(t_shell *shell, char **env);
		// handle_var_env
char	**update_env(char **env, const char *name, const char *value);
char	**remove_env_var(char **env, const char *name);

// Debug
void	print_shell_instance(t_shell *shell);

#endif
