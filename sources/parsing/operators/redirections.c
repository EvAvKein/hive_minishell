/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:22:52 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/27 20:32:13 by ekeinan          ###   ########.fr       */
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
 * @returns The new appended node
 *          (or `NULL` on parsing error or memory allocation failure).
 * 
 */
static t_node	*parse_redirection(
	t_parsing *parsing, size_t operator_len, bool heredoc)
{
	t_node	*new_node;

	parsing->i += operator_len;
	skip_spaces(parsing);
	new_node = append_new_node(1);
	if (!new_node)
		return (NULL);
	skip_spaces(parsing);
	new_node->argv[0] = extract_arg(parsing, heredoc);
	if (!new_node->argv[0])
		return (NULL);
	parsing->midparse_nodes++;
	return (new_node);
}

/**
 * 
 * Parses a heredoc operation from its (assumed) operator,
 * swaps the SIGINT action for the duration, and executes the heredoc.
 * 
 * @returns Whether heredoc parsing and execution were successful.
 * 
 */
bool	parse_heredoc(t_parsing *parsing)
{
	t_node	*heredoc_node;

	heredoc_node = parse_redirection(parsing, 2, true);
	if (!heredoc_node)
		return (false);
	heredoc_node->type = HEREDOC;
	if (!execute_heredoc(heredoc_node, is_delimiter_quoted(parsing)))
	{
		sigaction(SIGINT,
			&(struct sigaction){.sa_sigaction = sigint_handler}, NULL);
		return (false);
	}
	return (true);
}

/**
 * 
 * Parses an appendfile operation from its (assumed) operator.
 * 
 * @returns Whether parsing and memory allocations were all successful.
 * 
 */
bool	parse_appendfile(t_parsing *parsing)
{
	t_node	*appendfile_node;

	appendfile_node = parse_redirection(parsing, 2, false);
	if (!appendfile_node)
		return (false);
	appendfile_node->type = APPENDFILE;
	return (true);
}

/**
 * 
 * Parses an infile operation from its (assumed) operator.
 * 
 * @returns Whether parsing and memory allocations were all successful.
 * 
 */
bool	parse_infile(t_parsing *parsing)
{
	t_node	*infile_node;

	infile_node = parse_redirection(parsing, 1, false);
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
bool	parse_outfile(t_parsing *parsing)
{
	t_node	*outfile_node;

	outfile_node = parse_redirection(parsing, 1, false);
	if (!outfile_node)
		return (false);
	outfile_node->type = OUTFILE;
	return (true);
}
