/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_void_expansions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:32:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/29 18:25:09 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @file These could've been two functions which would fit in expansion.c ,
 * but I created this file to split things up for readability - hope it helps!
 * 
 */

/**
 *
 * Whether the expansion has prefixed content,
 * making it impossible to result in one fewer argument
 * if the expansion has no value.
 * 
 * @param expansion A pointer to the string
 *                  which starts ('$') with the expansion.
 * 
 * @param input     The start of the user input
 *                  (for checking if it's safe to index backwards).
 * 
 * @return Whether the provided expansion has any content before it.
 * 
 */
static inline bool	has_prefixed_content(char *expansion, char *input)
{
	return ((expansion != input && !is_space(expansion[-1])
			&& !is_control_flow(expansion[-1])));
}

/**
 * 
 * Whether the expansion has postfixed content,
 * making it impossible to result in one fewer argument
 * if the expansion has no value.
 * 
 * @param expansion A pointer to the string
 *                  which starts ('$') with the expansion.
 * 
 * @param exp_len   The length of the expansion text (`$` plus variable length).
 * 
 * @return Whether the provided expansion has any content after it.
 * 
 */
static inline bool	has_postfixed_content(char *expansion, size_t exp_len)
{
	return (expansion[exp_len] && expansion[exp_len] != '$'
		&& !is_control_flow(expansion[exp_len]) && !is_space(expansion[exp_len])
		&& !is_quote(expansion[exp_len]));
}

/**
 * 
 * Checks whether the provided expansion would result
 * in one fewer argument if the expansion has no value - if it has a value,
 * this skips past the expansion.
 * 
 * If the provided expansion is not actually an expansion
 * (i.e. doesn't start with a '$'), skips to the next characters.
 *
 * @param expansion A pointer to a string which starts with '$',
 *                  to be potentially skipped past the expansion.
 * 
 * @param input     The user input being parsed.
 * 
 * @param exp_len   A pointer in which to set the expansion string's length,
 *                  gets set for external use.
 *                  
 *  
 * @returns Whether `expansion` was skipped.
 * 
 */
static inline bool	skipped_expansion(
	char **expansion, char *input, size_t *exp_len)
{
	if (!(*expansion)[1])
	{
		(*expansion) += 1;
		(*exp_len) = 1;
		return (true);
	}
	if ((*expansion)[1] == '$')
	{
		*expansion += 2;
		(*exp_len) = 2;
		return (true);
	}
	*exp_len = env_name_len(&((*expansion)[1])) + 1;
	if (has_prefixed_content(*expansion, input)
		|| has_postfixed_content(*expansion, *exp_len))
	{
		*expansion += *exp_len;
		return (true);
	}
	return (false);
}

/**
 * 
 * Delete all expansions which are not in quotes or part of an adjacent string,
 * replacing those expansions with space characters.
 * 
 * This is pre-parsing step
 * to ensure expansions with no value don't get expanded to an empty argument,
 * but rather resolve to no argument at all.
 * 
 * @param input The user input -
 *              gets modified as per this function's description.
 * 
 */
void	delete_void_expansions(char *input)
{
	char	*expansion;
	size_t	exp_len;
	char	in_quote;

	expansion = input;
	in_quote = '\0';
	while (expansion && *expansion)
	{
		if ((*expansion != '$' || in_quote
				|| toggle_quote_by_c(&in_quote, *expansion)))
		{
			expansion++;
			continue ;
		}
		if (skipped_expansion(&expansion, input, &exp_len))
			continue ;
		if (!env_value(&expansion[1]))
			ft_memset(expansion, ' ', exp_len);
		expansion += exp_len;
	}
}
