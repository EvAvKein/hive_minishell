/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:14:02 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/17 17:51:14 by ekeinan          ###   ########.fr       */
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

/* SETTINGS *******************************************************************/

// # ifndef VERBOSE
// #  define VERBOSE 0
// # endif

/* TYPES **********************************************************************/

typedef enum e_node_type
{
	PENDING = 0,
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
	t_node		*nodes;
}				t_shell;

/* PARSING FUNCTIONS **********************************************************/

bool	parsing(t_shell *shell);

t_node	*extract_args(char *input, size_t *i);

t_operator operator_of_c(char *c);
bool	handle_operator(t_shell *shell, t_node *preceding_node, size_t *i);

bool	toggle_quote_by_c(char *containing_quote, char c);

bool	parse_heredoc(t_shell *shell, t_node *preceding_node, size_t *i);
bool	parse_appendfile(t_shell *shell, t_node *preceding_node, size_t *i);
bool	parse_infile(t_shell *shell, t_node *preceding_node, size_t *i);
bool	parse_outfile(t_shell *shell, t_node *preceding_node, size_t *i);
bool	parse_equals(t_shell *shell, t_node *preceding_node, size_t *i);
bool	parse_plusequals(t_shell *shell, t_node *preceding_node, size_t *i);

/* EXECUTION FUNCTIONS ********************************************************/

void	execution(t_shell *shell);

/* UTILITY FUNCTIONS **********************************************************/

bool	is_space(char c);
bool	is_entirely_spaces(char *string);

/* CLEANUP FUNCTIONS **********************************************************/

void	shell_cleanup(t_shell *shell);
void	shell_exit(t_shell *shell, int exit_status);

void	free_nodes(t_node *node);
void	*free_2d_arr(void *arr, size_t length);

#endif
