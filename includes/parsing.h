/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:04:38 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/29 09:00:28 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

/* TYPES **********************************************************************/

typedef struct s_node t_node;

/**
 * 
 * The top-level information needed for parsing user input into a list of nodes.
 * 
 */
typedef	struct s_parsing
{
	char	*input;
	size_t	i;
	t_node	*node_before_command;
	t_node	*command_node;
	size_t	midparse_nodes;
	bool	piping;
}			t_parsing;

/**
 * 
 * An enum for improving the readability of flags used in redirection parsing.
 *  
 */
typedef enum e_redirect
{
	RDR_NONE = 0,
	RDR_HEREDOC,
	RDR_APPENDFILE,
	RDR_INFILE,
	RDR_OUTFILE,
}	t_redirect;

/* FUNCTION PARAM STRUCTS *****************************************************/

/**
 * 
 * Variables for reattaching a segment of sorted nodes (organized with `
 * t_node_sort`) into the primary linked list of nodes.
 * 
 */
typedef struct s_node_sort_reattach
{
	t_node	*start;
	t_node	*prev_node;
	t_node	*infiles;
	t_node	*outfiles;
}			t_node_sort_reattach;

/**
 * 
 * Variables for sorting a segment of nodes.
 * 
 * The initial order is `command -> all redirections`,
 * and these variables help turn it into `infiles -> command -> outfiles`.
 * 
 */
typedef struct s_node_sort
{
	t_node					*node;
	t_node					*command_node;
	size_t					infile_count;
	size_t					outfile_count;
	size_t					node_i_from_end;
	t_node					**infile_arr;
	t_node					**outfile_arr;
	t_node_sort_reattach	attach;
}							t_node_sort;

/**
 * 
 * Created solely for Norminette line-saving inside `str_to_argc`.
 * 
 */
typedef struct s_str_to_argc_vars
{
	size_t	i;
	int		argc;
	bool	in_arg;
	char	in_quote;
	char	in_redirect[3];
}			t_str_to_argc_vars;

/**
 * 
 * Created solely for Norminette line-saving inside `str_to_argv`.
 * 
 */
typedef struct s_str_to_argv_vars
{
	char	**argv;
	size_t	argv_i;
	size_t	arg_len;
}			t_str_to_argv_vars;

#endif
