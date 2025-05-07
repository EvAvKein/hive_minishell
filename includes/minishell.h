/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:14:02 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/12 13:27:59 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft_plus.h"
# include "parsing.h"

# define SHELL_NAME "shellGBTQ+"

# define SHELL_PROMPT "\
\001\x1b[1;38;2;162;77;167m\002shell\
\001\x1b[1;38;2;39;115;255m\002G\
\001\x1b[1;38;2;32;170;10m\002B\
\001\x1b[1;38;2;220;202;0m\002T\
\001\x1b[1;38;2;240;115;0m\002Q\
\001\x1b[1;38;2;228;3;3m\002 + \
\001\x1b[0m\002"

# define MAX_CMDS	256
# define READ		0
# define WRITE		1

/* SETTINGS *******************************************************************/

// # ifndef VERBOSE
// #  define VERBOSE 0
// # endif

/* TYPES **********************************************************************/

typedef enum e_node_type
{
	UNPARSED = 0,
	COMMAND,
	HEREDOC,
	HEREDOC_QUOTED,
	INFILE,
	OUTFILE,
	APPENDFILE
}	t_node_type;

typedef struct s_node
{
	struct s_node	*prev;
	t_node_type		type;
	int				argc;
	char			**argv;
	int				fd;
	struct s_node	*next;
}					t_node;

typedef struct s_exec
{
	pid_t	pids[MAX_CMDS];
	int		pid_count;
}			t_exec;

typedef struct s_shell
{
	char		**envp;
	char		**ms_envp;
	int			last_exit_status;
	t_node		*nodes;
	t_exec		*exec;
}				t_shell;

/* PARSING FUNCTIONS **********************************************************/

bool		parsing(t_shell *shell, char *input);

void		skip_to_first_node(t_node **node);
void		skip_to_last_node(t_node **node);
t_node		*append_new_node(t_shell *shell, int argc);

bool		envncmp(char *env_str, char *name_str, size_t cmp);
char		*env_value(t_shell *shell, char *var_name);
size_t		env_name_len(char *var_name, bool equal_ends);
size_t		expanded_len(t_shell *shell, char *expand_start);
bool		expand_into_dest(t_expand_into_dest_args var);

char		*extract_arg(t_shell *shell, t_parsing *parsing);
bool		extract_nodes(t_shell *shell, t_parsing *parsing);
bool		sort_nodes_segment(t_shell *shell, t_parsing *parsing);

void		count_segment_nodes(t_parsing *parsing, t_node_sort *sort);
bool		collect_segment_nodes(t_node_sort *sort);
t_node		*link_collected_nodes(t_node ***nodes_arr, size_t i);
void		reattach_nodes(t_parsing *parsing, t_node_sort_reattach *reattach);

void		skip_spaces(t_parsing *parsing);
void		set_prev_and_next(t_node *node, t_node *new_prev, t_node *new_next);

bool		toggle_quote_by_c(char *containing_quote, char c);

int			str_to_argc(char *str, t_str_to_argc_vars var);
bool		skip_pipe(t_parsing *parsing);
bool		handle_redirect(t_shell *shell, t_parsing *parsing);
bool		memorize_and_skip_redirect(char *str, size_t *i, char memory[3]);

bool		parse_heredoc(t_shell *shell, t_parsing *parsing);
bool		parse_appendfile(t_shell *shell, t_parsing *parsing);
bool		parse_infile(t_shell *shell, t_parsing *parsing);
bool		parse_outfile(t_shell *shell, t_parsing *parsing);
bool		parse_equals(t_shell *shell, t_parsing *parsing);
bool		parse_plusequals(t_shell *shell, t_parsing *parsing);

t_redirect	redirect_of_c(char *c);

/* EXECUTION FUNCTIONS ********************************************************/

int		check_redirections(t_node *current);
int 	*close_pipe_fds(int pipe_fd[2]);
char	**dup_envp(char **envp);
int		execute_builtin(t_shell *shell);
int		execute_command(t_shell *shell, t_node *current);
void    execute_last_pipeline_element(t_shell *shell, t_node *current, int prev_fd, int pipe_fd[2]);
void	execute_pipeline(t_shell *shell);
int		execute_sys_command(t_shell *shell, t_node *current);
void	execution(t_shell *shell);
void	fatal_error(t_shell *shell, char *msg);
int		fork_and_execute_sys_command(t_shell *shell);
void	free_env_array(char **env);
char	*get_pwd_from_env(char **envp);
int		get_env_elements(char **envp);
int		handle_appendfile(char *file);
int		handle_infile(char *file);
int		handle_outfile(char *file);
int		handle_outfiles(t_node *current);
int		is_builtin(char *cmd);
int		ms_cd(t_shell *shell);
void	ms_echo(t_shell *shell);
void	ms_env(t_shell *shell);
void	ms_exit(t_shell *shell);
int		ms_export(t_shell *shell);
void	ms_pipe(t_shell *shell);
void	ms_pwd(char **envp);
void	ms_unset(t_shell *shell);
void	pipeline_child(t_shell *shell, t_node *current, int prev_fd, int pipe_fd[2]);
void	wait_for_all_children(t_shell *shell);

/* UTILITY FUNCTIONS **********************************************************/

void		print_nodes(int fd, t_node *node);
void		print_node_type(int fd, t_node_type type);

bool		is_space(char c);
bool		is_entirely_spaces(char *string);
bool		input_was_entirely_spaces(char *input);

/* CLEANUP FUNCTIONS **********************************************************/

void		command_cleanup(t_shell *shell);
void		shell_cleanup(t_shell *shell);
void		shell_exit(t_shell *shell, int exit_status);

void		*free_nodes(t_node *node);
void		*free_2d_arr(void *arr, size_t length);

#endif
