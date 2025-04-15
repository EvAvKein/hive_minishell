/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:06:37 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/14 19:15:50 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * Validates whether a character is a skippable quote or not,
 * updating `in_quotes` accordingly.
 * 
 * @param in_quotes    Bools for whether we're already inside
 *                     single or double quotes respectively.
 *                     This function flips the booleans accordingly. 
 * 
 * @param c            A pointer to the char that this function should validate.
 *
 * @param has_previous Whether this character has a previous one,
 *                     i.e. if it's safe to check the previous memory address.
 * 
 * @returns Boolean, whether the quote is skippable.
 * 
 */
// bool	is_skippable_quote(bool in_quotes[2], char *c, bool has_previous)
// {
// 	if (*c == '\'')
// 	{
// 		if (in_quotes[1])
// 			return (false);
// 		if ((has_previous && c[-1] != '\'') || in_quotes[0])
// 		{
// 			in_quotes[0] = !in_quotes[0];
// 			return (true);
// 		}
// 	}
// 	if (*c == '"')
// 	{
// 		if (in_quotes[0])
// 			return (false);
// 		if ((has_previous && c[-1] != '"') || in_quotes[1])
// 		{
// 			in_quotes[1] = !in_quotes[1];
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

/**
 * 
 * Checks whether the character `c` in an opening/closing quote based on
 * `containing_quote`, toggling `containing_quote` accordingly
 * 
 * @param containing_quote An address to the type of the current opening quote
 *                         (`"`, `'`, or `\0`), to be potentially toggled.
 * 
 * @param c                The character being evaluated
 *                         to check whether `containing_quote` should be
 *                         toggled (if it's an opening/closing quote)
 *                         or not (if it's any other character).
 * 
 * @returns Whether `containing_quote` was toggled.
 * 
 */
bool	toggle_quote_by_c(char *containing_quote, char c)
{
	if (c == *containing_quote)
	{
		*containing_quote = '\0';
		return (true);
	}
	else if (!*containing_quote && (c == '\'' || c == '"'))
	{
		*containing_quote = c;
		return (true);
	}
	return (false);
}
