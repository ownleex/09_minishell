/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayarmaya <ayarmaya@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 02:36:34 by ayarmaya          #+#    #+#             */
/*   Updated: 2024/10/06 05:04:46 by ayarmaya         ###   ########.fr       */
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
	int				*has_single_quote;
	int				*was_quoted;
	struct s_shell	*next;
}	t_shell;

typedef struct s_context
{
	int				num_cmds;
	int				*pipes;
	pid_t			*pids;
	int				i;
}	t_context;

// Utils main
void	free_redirections(t_shell *shell);
void	free_shell(t_shell *shell);
void	free_all_shells(t_shell *shell);
void	void_argc_argv(int argc, char **argv);

// Init
void	ft_init(t_shell *shell);
int		initialize_shell(t_shell **shell, char ***env, char **envp);
void	init_context(t_context *context, t_shell *shell);

// Signal
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	handle_signaled_status(t_shell *shell, int status);
void	setup_signals(void);

// Parsing
void	handle_cmd(t_shell *shell);
void	parse_command(t_shell *shell);
	// Command_check_1
int		is_invalid_syntax(t_shell *shell);
	// Command_check_2
int		check_pipe_errors(t_shell *shell, int i);
int		check_redirection_errors(t_shell *shell, int i);
void	handle_syntax_error(t_shell *shell, int syntax_error);
	// Utils
int		is_quote(int c);
int		is_redirecion(char *str);
int		is_single_pipe(char *line, int p);
int		jump_quote(t_shell *shell, int cursor);
int		is_single_redirection(char *line, int p);
int		is_separator(int character, int space);
int		do_redirection(char *line, int index, int *len);
int		do_pipe(int index, int *len);
int		do_separator(char *line, int index, int *len);
void	copy_inner_content(char *dest, char *src, int start, int end);
	// Instances
void	allocate_instance(t_shell *instance, int arg_count);
void	handle_input_redirection(t_shell *shell, int i, t_shell *main_shell);
void	handle_output_redirection(t_shell *shell, int i, t_shell *main_shell);
	// Arguments
int		count_args(char *line);
int		jump_arg(char *line, int cursor);
int		get_arglen(t_shell *shell, int start, int end);
void	set_arg(t_shell *shell, int start, int end, int pos);
	// Addons
void	free_main_shell(t_shell *shell);
int		find_end(t_shell *shell, int start);
	// Expand_variables
void	expand_variables_in_args(t_shell *shell, char **env);

// Exec
void	execute_command(t_shell *shell, char ***env);
void	exec_commd_builtin(t_shell *shell, char **env, pid_t *pids, int *pipes);
int		count_commands(t_shell *shell);
	//Redirection
void	handle_redir(t_shell *shell, char **env, pid_t *pids, int *pipes);
	//Pipes
void	close_all_pipes(int *pipes, int num_pipes);
int		*initialize_pipes(int num_cmds);
	//fork_and_process
void	execute_child_process(t_shell *current_shell, char **env, \
t_context *context);
void	wait_for_processes(pid_t *pids, int num_procs, t_shell *shell);
int		initialize_pids(t_shell *shell, pid_t **pids);
	//Find_command_path
char	*find_command_path(t_shell *shell, char **env);
	//heredoc
void	handle_heredoc_if_needed(t_shell *shell);
	// Utils exec
void	free_array(char ***array);
void	free_args(t_shell *shell);

// Builtin
int		is_builtin(t_shell *shell);
int		is_builtin_without_pipe_or_redirect(t_shell *shell);
void	handle_builtin(t_shell *shell, char ***env, pid_t *pids, int *pipes);
	// Echo
void	ft_echo(t_shell *shell);
	// Pwd
void	ft_pwd(t_shell *shell);
	// Env
void	ft_env(t_shell *shell, char **env);
	// Exit
void	ft_exit(t_shell *shell, char **env, pid_t *pids, int *pipes);
	// CD
char	**ft_cd(t_shell *shell, char **env);
	// Export
char	**ft_export(t_shell *shell, char **env);
	// Unset
char	**ft_unset(t_shell *shell, char **env);
		// handle_var_env
			//export_update_env
char	**update_env(char **env, const char *name, const char *value);
			//unset_remove_env_var
char	**remove_env_var(char **env, const char *name);
			//cd_env
char	*get_home_directory(char **env);

#endif
