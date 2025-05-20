/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_flow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:23:07 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/19 22:07:56 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @param c The address of the character to be checked.
 *          If not falsy, assumed to be part of a null-terminated string.
 * 
 * @returns A value corresponding to the type of redirect it is (or if it isn't)
 * 
 */
t_redirect	redirect_of_c(char *c)
{
	if (!c || !*c)
		return (RDR_NONE);
	if (c[0] == '<' && c[1] == '<')
		return (RDR_HEREDOC);
	if (c[0] == '>' && c[1] == '>')
		return (RDR_APPENDFILE);
	if (*c == '<')
		return (RDR_INFILE);
	if (*c == '>')
		return (RDR_OUTFILE);
	return (RDR_NONE);
}

/**
 * 
 * Updates the provided `memory` array based on the character(s) in `
 * str[i]` (wiping the memory if it's not a redirect),
 * and skips the index past any redirect found.
 * 
 * @returns `true` (for external line-saving reason, due to Norminette).
 * 
 */
bool	memorize_and_skip_redirect(char *str, size_t *i, char memory[3])
{
	t_redirect	redirect;

	redirect = redirect_of_c(&str[*i]);
	if (redirect == RDR_HEREDOC && ++(*i) && ++(*i))
		ft_memcpy(memory, "<<", 2);
	else if (redirect == RDR_APPENDFILE && ++(*i) && ++(*i))
		ft_memcpy(memory, ">>", 2);
	else if (redirect == RDR_INFILE && ++(*i))
		ft_memcpy(memory, "<\0", 2);
	else if (redirect == RDR_OUTFILE && ++(*i))
		ft_memcpy(memory, ">\0", 2);
	else
		ft_memcpy(memory, "\0\0", 2);
	return (true);
}

/**
 * 
 * Checks if the current point in parsing is a redirect - if so, calls the
 * appropriate function for parsing that redirect.
 * 
 * @returns Whether the redirect parsing was successful,
 *          or `true` if the current point in parsing is not a redirect.
 * 
 */
bool	handle_redirect(t_parsing *parsing)
{
	t_redirect	redirect;

	redirect = redirect_of_c(&parsing->input[parsing->i]);
	if (redirect == RDR_HEREDOC)
		return (parse_heredoc(parsing));
	else if (redirect == RDR_APPENDFILE)
		return (parse_appendfile(parsing));
	else if (redirect == RDR_INFILE)
		return (parse_infile(parsing));
	else if (redirect == RDR_OUTFILE)
		return (parse_outfile(parsing));
	return (true);
}

/**
 * 
 * If parsing is currently at a pipe operator, skip past it and set the
 * appropriate flag.
 * 
 * @returns Whether a pipe was skipped.
 * 
 */
bool	skip_pipe(t_parsing *parsing)
{
	if (parsing->input[parsing->i] == '|')
	{
		parsing->i++;
		parsing->piping = true;
		return (true);
	}
	return (false);
}
