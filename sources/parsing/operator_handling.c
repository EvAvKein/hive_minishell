/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:23:07 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/17 15:46:26 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @param c The address of the character to be checked.
 *          If not falsey, assumed to be part of a null-terminated string.
 * 
 * @returns A value corresponding to the type of operator it is (or if it isn't)
 * 
 */
t_operator operator_of_c(char *c)
{
	if (!c || !*c)
		return (OPR_NONE);
	if (*c == '|')
		return (OPR_PIPE);
	if (c[0] == '<' && c[1] == '<')
		return (OPR_HEREDOC);
	if (c[0] == '>' && c[1] == '>')
		return (OPR_APPENDFILE);
	if (*c == '<')
		return (OPR_INFILE);
	if (*c == '>')
		return (OPR_OUTFILE);
	if (*c == '=')
		return (OPR_EQUALS);
	if (c[0] == '+' && c[1] == '=')
		return (OPR_PLUSEQUALS);
	return (OPR_NONE);
}

/**
 * 
 * TODO: Write these docs
 * 
 */
bool	handle_operator(t_shell *shell, t_node *preceding_node, size_t *i)
{
	t_operator	operator;

	operator = operator_of_c(&shell->latest_input[*i]);
	if (operator == OPR_HEREDOC)
		return (parse_heredoc(shell, preceding_node, i));
	else if (operator == OPR_APPENDFILE)
		return (parse_appendfile(shell, preceding_node, i));
	else if (operator == OPR_INFILE)
		return (parse_infile(shell, preceding_node, i));
	else if (operator == OPR_OUTFILE)
		return (parse_outfile(shell, preceding_node, i));
	else if (operator == OPR_EQUALS)
		return (parse_equals(shell, preceding_node, i));
	else if (operator == OPR_PLUSEQUALS)
		return (parse_plusequals(shell, preceding_node, i));
	else if (operator == OPR_PIPE)
		(*i)++;
	return (true);
}
