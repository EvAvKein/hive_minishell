/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:04:38 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/17 12:43:52 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

typedef enum e_operator
{
	OPR_NONE = 0,
	OPR_PIPE,
	OPR_HEREDOC,
	OPR_APPENDFILE,
	OPR_INFILE,
	OPR_OUTFILE,
	OPR_EQUALS,
	OPR_PLUSEQUALS
}	t_operator;

/**
 * 
 * Created solely for Norminette line-saving inside `str_to_argc`
 * 
 */
typedef struct s_str_to_argc_vars
{
	int		argc;
	size_t	i;
	char	in_quote;
	bool	in_arg;
}	t_str_to_argc_vars;

/**
 * 
 * Created solely for Norminette line-saving inside `arg_cpy`
 * 
 */
typedef struct s_argv_cpy_vars
{
	size_t		src_i;
	size_t		dest_i;
	char		in_quote;
}	t_argv_cpy_vars;

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
}	t_str_to_argv_vars;

#endif
