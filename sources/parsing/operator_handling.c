/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_handling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:23:07 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/25 16:42:12 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @param c The address of the character to be checked.
 *          If not falsy, assumed to be part of a null-terminated string.
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
 * Updates the provided `memory` array based on the character(s) in `
 * str[i]` (wiping the memory if it's no operator),
 * and skips the index past any operator found.
 * 
 * @returns `true` (for external line-saving reason, due to Norminette).
 * 
 */
bool	memorize_and_skip_operator(char *str, size_t *i, char memory[3])
{
	t_operator	operator;

	operator = operator_of_c(&str[*i]);
	if (operator == OPR_HEREDOC && ++(*i) && ++(*i))
		ft_memcpy(memory, "<<", 2);
	else if (operator == OPR_APPENDFILE && ++(*i) && ++(*i))
		ft_memcpy(memory, ">>", 2);
	else if (operator == OPR_INFILE && ++(*i))
		ft_memcpy(memory, "<\0", 2);
	else if (operator == OPR_OUTFILE && ++(*i))
		ft_memcpy(memory, ">", 2);
	else if (operator == OPR_EQUALS && ++(*i))
		ft_memcpy(memory, "=\0", 2);
	else if (operator == OPR_PLUSEQUALS && ++(*i) && ++(*i))
		ft_memcpy(memory, "+=", 2);
	// else if (operator == OPR_PIPE && (*i)++)
	// 	ft_memcpy(memory, "|\0", 2);
	else
		ft_memcpy(memory, "\0\0", 2);
	return (true);
}

/**
 * 
 * Checks if the current point in parsing is an operator - if so, calls the
 * appropriate function for parsing that operator.
 * 
 * @returns Whether the operator parsing was successful,
 *          or `true` if the current point in parsing is not an operator.
 * 
 */
bool	handle_operator(t_shell *shell, t_parsing *parsing)
{
	t_operator	operator;

	operator = operator_of_c(&parsing->input[parsing->i]);
	if (operator == OPR_HEREDOC)
		return (parse_heredoc(shell, parsing));
	else if (operator == OPR_APPENDFILE)
		return (parse_appendfile(shell, parsing));
	else if (operator == OPR_INFILE)
		return (parse_infile(shell, parsing));
	else if (operator == OPR_OUTFILE)
		return (parse_outfile(shell, parsing));
	else if (operator == OPR_EQUALS)
		return (parse_equals(shell, parsing));
	else if (operator == OPR_PLUSEQUALS)
		return (parse_plusequals(shell, parsing));
	else if (operator == OPR_PIPE)
		parsing->i++;
	return (true);
}
