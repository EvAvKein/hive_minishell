/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:04:38 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/28 09:23:49 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

/* TYPES **********************************************************************/

typedef struct s_node t_node;

/**
 * 
 * TODO: Write these docs
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
 * TODO: Write these docs
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
 * TODO: Write these docs
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
 * TODO: Write these docs
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
 * Created solely for Norminette line-saving inside `str_to_argc`
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
 * Created solely for Norminette line-saving inside `str_to_argv`
 * 
 */
typedef struct s_str_to_argv_vars
{
	char	**argv;
	size_t	argv_i;
	size_t	arg_len;
}			t_str_to_argv_vars;

#endif
