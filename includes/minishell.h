/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:14:02 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/23 14:15:21 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <stdio.h>
# include "libft_plus.h"

/* TYPES **********************************************************************/

typedef enum e_node_type
{
	INVALID,
	COMMAND,
	HEREDOC,
	INFILE,
	OUTFILE,
	APPENDFILE
}	t_node_type;

typedef struct s_node
{
	t_node_type		type;
	int				argc;
	char			**argv;
	struct s_node	*next;	
}					t_node;

typedef struct s_shell
{
	char		*latest_input;
	char		**env;
	char		**ms_envp;
	int			last_exit_status;
	t_node		*nodes;
}				t_shell;

/* PARSING FUNCTIONS **********************************************************/

void	parsing(t_shell *shell);

bool	toggle_quote_by_c(char *containing_quote, char c);

/* EXECUTION FUNCTIONS ********************************************************/

char	**dup_envp(char **envp);
int		execute_builtin(t_shell *shell);
int		execute_sys_command(t_shell *shell);
void	execution(t_shell *shell);
int		fork_and_execute_sys_command(t_shell *shell);
void	free_env_array(char **env);
int		get_env_elements(char **envp);
char	*get_path_from_arg(t_shell *shell);
char	*get_path_from_envp(t_shell *shell);
void	ms_cd(t_shell *shell);
void	ms_echo(t_shell *shell);
void	ms_env(t_shell *shell);
void	execute_command(t_shell *shell);
int		execute_appendfile(char *file);
int		execute_infile(char *file);
int		execute_outfile(char *file);
void	ms_exit(t_shell *shell);
void	ms_export(t_shell *shell);
void	ms_pwd(void);
void	ms_unset(t_shell *shell);

/* UTILITY FUNCTIONS **********************************************************/

int		is_builtin(char *cmd);
bool	is_space(char c);
bool 	is_entirely_spaces(char *string);

/* CLEANUP FUNCTIONS **********************************************************/

void	shell_cleanup(t_shell *shell);
void	shell_exit(t_shell *shell, int exit_status);

void	free_nodes(t_node *node);
void	*free_2d_arr(void *arr, size_t length);

#endif
