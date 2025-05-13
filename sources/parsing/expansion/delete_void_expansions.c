/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_void_expansions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:32:55 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/13 15:02:32 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @file These could've been two functions which would fit in expansion.c ,
 * but I've created this file to split things up for readability.
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
 */
static inline bool	has_prefixed_content(char *expansion, char *input)
{
	return ((expansion != input && !is_space(expansion[-1])
		&& (expansion[-1] == '\'' || expansion[-1] == '"'
			|| !is_invalid_identifier(expansion[-1]))));
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
 */
static inline bool	has_postfixed_content(
	char *expansion, char *in_quote, size_t exp_len)
{
	return (
		expansion[exp_len] && !is_space(expansion[exp_len])
		&& !*in_quote
		&& (expansion[exp_len] == '"' || expansion[exp_len] == '\''));
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
 * @param expansion A pointer to a string which starts with '$'.
 *  
 * @returns Whether something was skipped.
 * 
 */
static inline bool	skipped_expansion(
	char **expansion, char *input, char *in_quote, size_t *exp_len)
{
	if (!(*expansion)[1])
	{
		(*expansion) += 1;
		return (true);
	}
	if ((*expansion)[1] == '$')
	{
		*expansion += 2;
		return (true);
	}
	*exp_len = env_name_len(&((*expansion)[1]), false) + 1;
	if (has_prefixed_content(*expansion, input)
		|| has_postfixed_content(*expansion, in_quote, *exp_len))
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
void	delete_void_expansions(t_shell *shell, char *input)
{
	char	*expansion;
	size_t	exp_len;
	char	in_quote;

	expansion = input;
	in_quote = '\0';
	while (expansion && *expansion)
	{
		if (!expansion)
			break ;
		if ((toggle_quote_by_c(&in_quote, *expansion) || in_quote)
			|| *expansion != '$')
		{
			expansion += 1;
			continue ;
		}
		if (skipped_expansion(&expansion, input, &in_quote, &exp_len))
			continue ;
		if (env_value(shell, &expansion[1]))
			expansion += exp_len;
		else
			ft_memset(expansion, ' ', exp_len);
		expansion++;
	}
}
