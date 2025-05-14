/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tiny_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 17:32:38 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/14 17:37:04 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @returns Whether the provided `c` is a quote
 *          (single-quote or double-quote).
 * 
 */
inline bool	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

/**
 * 
 * @returns Whether the provided `c` is a supported control-flow character
 *          (redirection or pipe).
 * 
 */
inline bool	is_control_flow(char c)
{
	return (c == '<' || c == '>' || c == '|');	
}

/**
 * 
 * @returns Whether the provided `c` is a space character
 * (an actual space, or horizontal/vertical tab, or newline,
 * or form feed, or carriage return).
 * 
 */
inline bool	is_space(char c)
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
