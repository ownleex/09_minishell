
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
    // Exit
void    ft_exit(t_minishell *shell);

//Signal
void	handle_sigint(int sig);
void	setup_signals(void);

//Utils main

//Utils exec
void	free_array(char **array);
void	free_args(t_minishell *shell);



#include "minishell.h"

#include "minishell.h"

void	ft_init(t_minishell *shell, char **envp)
{
	int		i;
	int		envp_len;

	envp_len = 0;
	while (envp[envp_len])
		envp_len++;
	shell->envp = (char **)malloc(sizeof(char *) * (envp_len + 1));
	if (!shell->envp)
	{
		perror("malloc");
		free(shell);
		return ;
	}
	i = 0;
	while (i < envp_len)
	{
		shell->envp[i] = ft_strdup(envp[i]);
		if (!shell->envp[i])
		{
			perror("strdup");
			while (i > 0)
				free(shell->envp[--i]);
			free(shell->envp);
			free(shell);
			return ;
		}
		i++;
	}
	shell->envp[i] = NULL;
	shell->target_path = NULL;
	shell->current_path = getcwd(NULL, 0);
	if (!shell->current_path)
	{
		perror("getcwd");
		i = 0;
		while (shell->envp[i])
			free(shell->envp[i++]);
		free(shell->envp);
		free(shell);
		return ;
	}
}

void	void_argc_argv(int argc, char **argv)
{
	(void)argc;
	(void)argv;
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	shell;

	void_argc_argv(argc, argv);
	ft_init(&shell, envp);
	setup_signals();
	while (1)
	{
		shell.current_line = readline("minishell$> ");
		if (shell.current_line == NULL)
		{
			printf("\b exit\n");
			break ;
		}
		if (ft_strlen(shell.current_line) > 0)
		{
			add_history(shell.current_line);
			parse_command(&shell);
			execute_command(&shell);
		}
	}
	rl_clear_history();
	free(shell.current_path);
	free_array(shell.envp);
	return (0);
}

#include "minishell.h"

char	*find_command_path(t_minishell *shell)
{
	char	**path_split;
	char	*path;
	char	*full_path;
	char	*temp;
	int		i;

	path = NULL;
	i = 0;
	while (shell->envp[i])
	{
		path_split = ft_split(shell->envp[i], '=');
		if (ft_strncmp(path_split[0], "PATH", 4) == 0)
		{
			path = ft_strdup(path_split[1]);
			free_array(path_split);
			break ;
		}
		free_array(path_split);
		i++;
	}
	if (!path)
		return (NULL);
	path_split = ft_split(path, ':');
	free(path);
	i = 0;
	while (path_split[i])
	{
		full_path = ft_strjoin(path_split[i], "/");
		temp = full_path;
		full_path = ft_strjoin(full_path, shell->current_cmd);
		free(temp);
		if (access(full_path, X_OK) == 0)
		{
			free_array(path_split);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_array(path_split);
	return (NULL);
}

void	execute_command(t_minishell *shell)
{
	pid_t	pid;

	if (is_builtin(shell))
	{
		handle_builtin(shell);
		return (free_args(shell));
	}
	shell->command_path = find_command_path(shell);
	if (shell->command_path == NULL)
	{
		write(STDERR_FILENO, "bash: ", 7);
		write(STDERR_FILENO, shell->current_cmd, ft_strlen(shell->current_cmd));
		write(STDERR_FILENO, ": Command not found\n", 21);
		return (free_args(shell));
	}
	pid = fork();
	if (pid == 0)
	{
		if (execve(shell->command_path, shell->current_arg, shell->envp) == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror("minishell");
	else
		waitpid(pid, NULL, 0);
	free(shell->command_path);
	free_args(shell);
}

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	free_args(t_minishell *shell)
{
	int	i;

	if (!shell || !shell->current_arg)
		return ;
	i = 0;
	while (shell->current_arg[i])
	{
		if (shell->current_arg[i] != NULL)
		{
			free(shell->current_arg[i]);
			shell->current_arg[i] = NULL;
		}
		i++;
	}
	free(shell->current_arg);
	shell->current_arg = NULL;
}

#include "minishell.h"

int	is_separator(int character)
{
	if (character == 34 || character == 39)
		return (1);
	return (0);
}

int	count_len(char *line)
{
	int	len;
	int	index;

	len = 0;
	index = 0;
	while (line[index])
	{
		if (line[index] == ' ')
			index++;
		else
		{
			len++;
			while (line[index] && line[index] != ' ')
				index++;
		}
	}
	return (len);
}

int	get_arglen(t_minishell *shell, int start, int end)
{
	int	len;
	int	index;
	int	cursor;

	len = 0;
	index = start;
	cursor = 0;
	while (shell->current_line[index] && index <= end)
	{
		if (is_separator(shell->current_line[index]))
		{
			cursor = index + 1;
			while (shell->current_line[cursor] && shell->current_line[cursor] != shell->current_line[index])
			{
				len++;
				cursor++;
			}
			index = cursor;
		}
		else
			len++;
		index++;
	}
	return (len);
}

int	set_cmd(t_minishell *shell, char **arguments)
{
	int	len;
	int	index;

	len = 0;
	index = 0;
	while (shell->current_line[len] != ' ' && shell->current_line[len])
		len++;
	arguments[0] = (char *)malloc(sizeof(char) * (len + 1));
	while (shell->current_line[index] != ' ' && shell->current_line[index])
	{
		arguments[0][index] = shell->current_line[index];
		index++;
	}
	arguments[0][index] = '\0';
	return (len);
}

void	set_arg(t_minishell *shell, int start, int end, int pos, char **arguments)
{
	int		len;
	int		index;
	int		arg_index;
	char	quote;

	arg_index = 0;
	index = start;
	len = get_arglen(shell, start, end);
	arguments[pos] = (char *)malloc(sizeof(char) * (len + 1));
	while (shell->current_line[index] && index <= end)
	{
		if (is_separator(shell->current_line[index]))
		{
			quote = shell->current_line[index];
			index++;
			while (shell->current_line[index] && shell->current_line[index] != quote)
				arguments[pos][arg_index++] = shell->current_line[index++];
			if (shell->current_line[index] == quote)
				index++;
		}
		else
			arguments[pos][arg_index++] = shell->current_line[index++];
	}
	arguments[pos][arg_index] = '\0';
}

char	**set_arguments(t_minishell *shell, int arg_len)
{
	int	len;
	int	index;
	int	cursor;
	char	**arguments;

	len = 0;
	arguments = (char **)malloc(sizeof(char *) * (arg_len + 1));
	index = set_cmd(shell, arguments);
	while (shell->current_line[index])
	{
		if (shell->current_line[index] == ' ')
			index++;
		else
		{
			len++;
			cursor = index;
			while (shell->current_line[index] && shell->current_line[index] != ' ')
				index++;
			set_arg(shell, cursor, index - 1, len, arguments);
		}
	}
	arguments[len + 1] = NULL;
	return (arguments);
}

void	parse_command(t_minishell *shell)
{
	shell->current_arg = set_arguments(shell, count_len(shell->current_line));
	shell->current_cmd = shell->current_arg[0];
}

#include "minishell.h"

void	ft_env(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
		i++;
	}
}

#include "minishell.h"

void	ft_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX))
		printf("%s\n", cwd);
	else
		perror("pwd");
}

#include "minishell.h"

void	ft_exit(t_minishell *shell)
{
	int	exit_code;

	if (shell->current_arg[1])
		exit_code = ft_atoi(shell->current_arg[1]);
	else
		exit_code = 0;
	free(shell->current_path);
	free_args(shell);
	rl_clear_history();
	printf("exit\n");
	exit(exit_code);
}

#include "minishell.h"

int	is_builtin(t_minishell *shell)
{
	if (ft_strncmp(shell->current_cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(shell->current_cmd, "exit", 4) == 0)
		return (1);
	return (0);
}

void	handle_builtin(t_minishell *shell)
{
	if (ft_strncmp(shell->current_cmd, "echo", 4) == 0)
		ft_echo(shell);
	else if (ft_strncmp(shell->current_cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(shell->current_cmd, "env", 3) == 0)
		ft_env(shell);
	else if (ft_strncmp(shell->current_cmd, "cd", 2) == 0)
		ft_cd(shell);
	else if (ft_strncmp(shell->current_cmd, "exit", 4) == 0)
		ft_exit(shell);
}

#include "minishell.h"

int	get_envp_size(char **envp)
{
	int	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

void	update_env(t_minishell *shell, const char *name, const char *value)
{
	int		i;
	int		name_len;
	int		value_len;
	int		envp_size;
	char	*new_var;
	char	**new_envp;

	name_len = ft_strlen(name);
	value_len = ft_strlen(value);
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], name, name_len) == 0 && shell->envp[i][name_len] == '=')
		{
			free(shell->envp[i]);
			new_var = (char *)malloc(name_len + value_len + 2);
			if (!new_var)
				return ;
			ft_strlcpy(new_var, name, name_len + 1);
			ft_strlcat(new_var, "=", name_len + 2);
			ft_strlcat(new_var, value, name_len + value_len + 2);
			shell->envp[i] = new_var;
			return ;
		}
		i++;
	}
	envp_size = get_envp_size(shell->envp);
	new_envp = (char **)malloc(sizeof(char *) * (envp_size + 2));
	if (!new_envp)
		return ;
	i = 0;
	while (i < envp_size)
	{
		new_envp[i] = shell->envp[i];
		i++;
	}
	new_var = (char *)malloc(name_len + value_len + 2);
	if (!new_var)
		return ;
	ft_strlcpy(new_var, name, name_len + 1);
	ft_strlcat(new_var, "=", name_len + 2);
	ft_strlcat(new_var, value, name_len + value_len + 2);
	new_envp[envp_size] = new_var;
	new_envp[envp_size + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
}

void	ft_cd(t_minishell *shell)
{
	int		ret;
	char	*path;
	char	*oldpwd;
	char	*new_path;

	if (!shell->current_arg[1])
		return ;
	path = shell->current_arg[1];
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
	{
		perror("getcwd");
		return ;
	}
	ret = chdir(path);
	if (ret == -1)
	{
		perror("bash: cd");
		free(oldpwd);
		return ;
	}
	update_env(shell, "OLDPWD", oldpwd);
	free(oldpwd);
	new_path = getcwd(NULL, 0);
	if (!new_path)
	{
		perror("getcwd");
		return ;
	}
	update_env(shell, "PWD", new_path);
	free(shell->current_path);
	shell->current_path = new_path;
}

#include "minishell.h"

void	ft_echo(t_minishell *shell)
{
	int		i;

	i = 1;
	while (shell->current_arg[i])
	{
		if (i > 1)
			printf(" ");
		printf("%s", shell->current_arg[i]);
		i++;
	}
	printf("\n");
}

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	printf("\n");
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
