/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:14:02 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/29 09:51:15 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _XOPEN_SOURCE 700 // fixes vscode issue with struct sigaction

# include <fcntl.h>
# include <errno.h>
# include <signal.h> /** TODO: Discuss potentially unused */
# include <sys/wait.h>
# include <dirent.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft_plus.h"
# include "parsing.h"
# include "execution.h"

# define SHELL_NAME "shellGBTQ+"

# define PROMPT_START "\
\001\x1b[1;38;2;162;77;167m\002shell\
\001\x1b[1;38;2;39;115;255m\002G\
\001\x1b[1;38;2;32;170;10m\002B\
\001\x1b[1;38;2;220;202;0m\002T\
\001\x1b[1;38;2;240;115;0m\002Q\
\001\x1b[1;38;2;228;3;3m\002+\
\001\x1b[0m\002:"
# define PROMPT_PATH_PLACEHOLDER "[UNKNOWN PATH]"
# define PROMPT_END "\001\x1b[1;38;2;228;3;3m\002#\001\x1b[0m\002 "
// # define PROMPT_END "\001\x1b[1;38;2;240;115;0m\002#\001\x1b[0m\002"


/* SETTINGS *******************************************************************/

# ifndef VERBOSE
#  define VERBOSE 0
# endif

# ifndef AUTO_LS_LIMIT
#  define AUTO_LS_LIMIT 500
# endif

/* TYPES **********************************************************************/

typedef enum e_exit_status
{
	EXIT_INCORRECT =		2,
	EXIT_CMD_NOT_EXEC =		126,
	EXIT_CMD_NOT_FOUND =	127,
	EXIT_CMD_ERROR =		128,
}	t_node_status;

typedef	struct s_dirinfo
{
	DIR		*dir;
	char	*str;
	size_t	strlen;
	size_t	i;
} t_dirinfo;

typedef enum e_node_type
{
	UNPARSED = 0,
	COMMAND,
	HEREDOC,
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

typedef struct s_shell
{
	char		pid[20];
	char		**env;
	char		*working_dir;
	t_node		*nodes;
	bool		heredoc_aborted;
	int			last_exit_status;
	t_exec		exec;
}				t_shell;

char		*shell_prompt();

/* PARSING FUNCTIONS **********************************************************/

bool		parsing(char *input);

void		delete_void_expansions(char *input);

void		skip_to_first_node(t_node **node);
void		skip_to_last_node(t_node **node);
t_node		*append_new_node(int argc);

size_t		expanded_len(char *expand_start);
bool		expand_into_dest(t_expand_into_dest_args var);

char		*extract_arg(t_parsing *parsing, bool disable_expansion);
bool		extract_nodes(t_parsing *parsing);
bool		sort_nodes_segment(t_parsing *parsing);

void		count_segment_nodes(t_parsing *parsing, t_node_sort *sort);
bool		collect_segment_nodes(t_node_sort *sort);
t_node		*link_collected_nodes(t_node ***nodes_arr, size_t i);
void		reattach_nodes(t_parsing *parsing, t_node_sort_reattach *reattach);

void		skip_spaces(t_parsing *parsing);
void		set_prev_and_next(t_node *node, t_node *new_prev, t_node *new_next);

bool		toggle_quote_by_c(char *containing_quote, char c);

int			str_to_argc(char *str, t_str_to_argc_vars var);
bool		skip_pipe(t_parsing *parsing);
bool		handle_redirect(t_parsing *parsing);
bool		memorize_and_skip_redirect(char *str, size_t *i, char memory[3]);

size_t		count_digits(int num);
char		*itoa_to_buf(int integer, char *buf);
char		*pid_to_buf(char buf[20]);

bool		is_delimiter_quoted(t_parsing *parsing);
void		increment_postfixed_num(char *buffer);
bool		execute_heredoc(t_node *node, bool expand);

bool		parse_heredoc(t_parsing *parsing);
bool		parse_appendfile(t_parsing *parsing);
bool		parse_infile(t_parsing *parsing);
bool		parse_outfile(t_parsing *parsing);

t_redirect	redirect_of_c(char *c);

/* EXECUTION FUNCTIONS ********************************************************/

void		close_pipe(t_fd *fd);
int			count_commands(t_shell *shell);
int			count_outfiles(t_shell *shell);
int			count_redirections(t_shell *shell);
int			execute_builtin(t_shell *shell, t_node *command);
void		execute_command(t_shell *shell, t_node *command);
void		execute_command_line(t_shell *shell, t_fd *fd);
void		execute_ext_command(t_shell *shell, t_node *current);
void		execution(t_shell *shell);
void		fatal_error(t_shell *shell, char *msg);
void		fd_cleanup(t_fd *fd);
char		*get_pwd_from_env(char **envp);
char		*get_env(char **envp, char *find);
int			get_env_elements(char **envp);
int			is_builtin(char *cmd);
bool		is_builtin_in_parent(t_node *nodes);
void		export_just_print(t_shell *shell);
int			ms_cd(t_shell *shell);
int			ms_echo(t_shell *shell, t_node *command);
int			ms_env(t_shell *shell);
void		ms_exit(t_shell *shell);
int			ms_export(t_shell *shell);
int			ms_pwd(char **envp);
int			ms_unset(t_shell *shell);
int			open_redirections(t_shell *shell);
void		pipeline_child(t_shell *shell, t_node *command, t_fd *fd, t_node *current);
int			parent_and_child(int pid, t_fd *fd, t_node *command, t_node *current);
void		wait_for_all_children(t_shell *shell);

/* ENV FUNCTIONS **************************************************************/

void		init_env(char **envp);
char		**env_dup(char **env);
bool		env_add(char *new_var);
bool		env_remove(char *var_to_remove);

char		**env_var_ptr(char *var_name);

bool		is_envname_char(char c);
bool		is_valid_envname(char *new_env);
bool		envncmp(char *env_str, char *name_str, size_t cmp);
char		*env_value(char *var_name);
size_t		env_name_len(char *var_name);

/* SIGNAL FUNCTIONS ***********************************************************/

void		init_signal_handlers(void);
void		set_child_signal_handlers(void);
void		sigint_handler(int sig, siginfo_t *info, void *prevact);
void		sigpipe_handler(int sig, siginfo_t *info, void *prevact);
void		heredoc_sigint_handler(int sig);

/* UTILITY FUNCTIONS **********************************************************/

t_shell		*get_shell(void);

size_t		str_arr_count(char **str_arr);
char		**str_arr_shallow_copy(char **str_arr);
void		*free_str_arr(char **arr);
char		*str_arr_join(char **arr);

size_t		print_err(char *part1, char *part2);
void		print_nodes(int fd, t_node *node);
void		print_node_type(int fd, t_node_type type);

bool		is_quote(char c);
bool		is_control_flow(char c);
bool		is_space(char c);
bool		is_entirely_spaces(char *string);
bool		input_was_entirely_spaces(char *input);

/* CLEANUP FUNCTIONS **********************************************************/

void		*free_nodes(t_node *node);
void		command_cleanup();
void		shell_cleanup();
void		shell_exit(int exit_status);

#endif
