/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 08:14:02 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/10 08:24:33 by ekeinan          ###   ########.fr       */
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

/* TYPES **********************************************************************/

typedef enum	e_node_type
{
	INVALID,
	COMMAND,
	HEREDOC,
	INFILE,
	OUTFILE,
	APPENDFILE
}				t_node_type;

typedef struct s_node
{
	t_node_type		type;
	int				argc;
	char			**argv;
	struct s_node	*next;	
}					t_node;

typedef struct	s_shell
{
	char		*latest_input;
	char		**env;
	t_node		*nodes;
}				t_shell;

/* PARSING FUNCTIONS **********************************************************/

void	parsing(t_shell *shell);

t_node	*input_to_nodes(char *input);

/* EXECUTION FUNCTIONS ********************************************************/

void	execution(t_shell *shell);

/* UTILITY FUNCTIONS **********************************************************/

bool is_space(char c);
bool is_entirely_spaces(char *string);

/* CLEANUP FUNCTIONS **********************************************************/

void	shell_cleanup(t_shell *shell);
void	shell_exit(t_shell *shell, int exit_status);

void	free_nodes(t_node *node);
void	free_2d_arr(void *arr, size_t length);

#endif
