/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 09:36:35 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/14 08:55:11 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 *
 * Parses past the upcoming redirection operator, appending its new node to the
 * list with its argument.
 *
 * @param operator_len The length of the redirection operator being skipped,
 *                     for adding to the parsing index at the very start.
 *  
 * @returns The new appended node,
 *          or `NULL` on parsing error or memory allocation failure.
 * 
 */
static t_node	*parse_redirection(
	t_shell *shell, t_parsing *parsing, size_t operator_len)
{
	t_node	*new_node;

	parsing->i += operator_len;
	skip_spaces(parsing);
	new_node = append_new_node(shell, 1);
	if (!new_node)
		return (NULL);
	skip_spaces(parsing);
	new_node->argv[0] = extract_arg(shell, parsing);
	if (!new_node->argv[0])
		return (NULL);
	parsing->midparse_nodes++;
	return (new_node);
}

/**
 * 
 * Parses an appendfile operation from its (assumed) operator.
 * 
 * @returns Whether parsing and memory allocations were all successful.
 * 
 */
bool	parse_appendfile(t_shell *shell, t_parsing *parsing)
{
	t_node	*appendfile_node;
	
	// printf("Appendfile detected: \"%.2s\" @ i-%lu\n",
	// 	&parsing->input[parsing->i], parsing->i);
	appendfile_node = parse_redirection(shell, parsing, 2);
	if (!appendfile_node)
		return (false);
	appendfile_node->type = APPENDFILE;
	return (true);
}

/**
 * 
 * Parses a heredoc operation from its (assumed) operator.
 * 
 * @returns Whether parsing and memory allocations were all successful.
 * 
 */
bool	parse_heredoc(t_shell *shell, t_parsing *parsing)
{
	t_node	*heredoc_node;
	
	// printf("Heredoc detected: \"%.2s\" @ i-%lu\n",
	// 	&parsing->input[parsing->i], parsing->i);
	heredoc_node = parse_redirection(shell, parsing, 2);
	if (!heredoc_node)
		return (false);
	heredoc_node->type = HEREDOC;
	return (true);
}

/**
 * 
 * Parses an infile operation from its (assumed) operator.
 * 
 * @returns Whether parsing and memory allocations were all successful.
 * 
 */
bool	parse_infile(t_shell *shell, t_parsing *parsing)
{
	t_node	*infile_node;
	
	// printf("Infile detected: '%c' @ i-%lu\n",
	// 	parsing->input[parsing->i], parsing->i);
	infile_node = parse_redirection(shell, parsing, 1);
	if (!infile_node)
		return (false);
	infile_node->type = INFILE;
	return (true);
}

/**
 * 
 * Parses an outfile operation from its (assumed) operator.
 * 
 * @returns Whether parsing and memory allocations were all successful.
 * 
 */
bool	parse_outfile(t_shell *shell, t_parsing *parsing)
{
	t_node	*outfile_node;
	
	// printf("Outfile detected: '%c' @ i-%lu\n",
	// 	parsing->input[parsing->i], parsing->i);
	outfile_node = parse_redirection(shell, parsing, 1);
	if (!outfile_node)
		return (false);
	outfile_node->type = OUTFILE;
	return (true);
}
