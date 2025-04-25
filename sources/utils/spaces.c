/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:21:54 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/25 14:48:41 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file We don't need a file just for space-related functions.
 *       Combine into larger utils file when we have other utils.
 */

#include "minishell.h"

/**
 * 
 * @returns Whether the provided `c` is a space character
 * (an actual space, or horizontal/vertical tab, or newline,
 * or form feed, or carriage return)
 * 
 */
bool	is_space(char c)
{
	return (c == ' ' || (c <= '\r' && c >= '\t'));
}

/**
 * 
 * @returns Whether the provided `string` contains exclusively space characters
 * (as per the above `is_space` function).
 * 
 */
bool	is_entirely_spaces(char *string)
{
	if (!string)
		return (false);
	while (is_space(*string))
		string++;
	return (*string == '\0');
}

/**
 * 
 * Checks if the provided string contains only space characters,
 * deallocating that string's memory if so. 
 * 
 * @returns Whether the input was entirely spaces.
 * 
 */
bool	input_was_entirely_spaces(char *input)
{
	if (is_entirely_spaces(input))
	{
		free(input);
		return (true);
	}
	return (false);
}
