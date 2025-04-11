/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:39:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/11 09:43:30 by ekeinan          ###   ########.fr       */
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
 * Cases to keep in mind:
 * 
 * - `'echo' string`: valid
 * 
 * - `ec''ho string`: valid
 * 
 * - `ec'''ho' string`: valid
 * 
 * - `ec"''"ho string`: invalid
 * 
 * 
 */
static bool	is_skippable_quote(bool in_quotes[2], char *c, bool has_previous)
{
	if (*c == '\'')
	{
		if (in_quotes[1])
			return (false);
		if ((has_previous && *(c - 1) != '\'') || in_quotes[0])
		{
			in_quotes[0] = !in_quotes[0];
			return (true);
		}
	}
	if (*c == '"')
	{
		if (in_quotes[0])
			return (false);
		if ((has_previous && *(c - 1) != '"') || in_quotes[1])
		{
			in_quotes[1] = !in_quotes[1];
			return (true);
		}
	}
	return (false);
}

/**
 * Counts the length of an argument in a given string,
 * omitting quotes that should be parsed away
 * and including spaces within quotes.
 * 
 * Can optionally receive an index pointer to be incremented past the arg.
 * 
 * @param arg        The string for which to calucate the argument length.
 * 
 * @param external_i Pointer to an external index for this string,
 *                   to be incremented during this parsing until past the arg.
 *                   Pass `NULL` if there's not need for this.
 * 
 * NEWS FLASH DUMMMY (me!), YOU CAN REPLACE WITH THIS A QUOTE VAR THAT SKIPS
 * UNTIL REACHING THE CURRENT QUOTE AGAIN.
 * DON'T INCREASE LEN WHEN AT OPENING/CLOSING QUOTE
 *
 */
static int	arg_len(char *arg, size_t *external_i)
{
	size_t		i;
	size_t		length;
	char		in_quote;
	const bool	in_quotes[2] = {false, false};

	i = 0;
	length = 0;
	in_quote = '\0';
	while (arg[i])
	{
		length++;
		if (external_i)
			(*external_i)++;
		if (is_space(arg[i]))
		{
			if (in_quote && ++length && ++i)
				continue;
			return (length);
		}
		if ((arg[i] == '\'' || arg[i] == '"')
			&& arg[i] == )
			length--;
		i++;
	}
	return (length);
}

////////////////////

static int	input_to_argc(char *input)
{
	// size_t		i;
	// int			argc;
	// bool		in_arg;
	// const bool	in_quotes[2] = {false, false};

	// i = 0;
	// argc = 0;
	// in_arg = false;
	// while (input[i])
	// {
	// 	length++;
	// 	if (external_i)
	// 		(*external_i)++;
	// 	if (is_space(arg[i]))
	// 	{
	// 		if ((in_quotes[0] || in_quotes[1]) && ++length && ++i)
	// 			continue;
	// 		return (length);
	// 	}
	// 	if ((arg[i] == '\'' || arg[i] == '"')
	// 		&& is_skippable_quote(in_quotes, arg[i], i))
	// 		length--;
	// 	i++;
	// }
	// return (length);
}
void	parsing(t_shell *shell)
{
	char	*input;
	size_t	token_start_i;
	size_t	token_len;
	size_t	parse_i;
	const bool	in_quotes[2] = {false, false};

	input = shell->latest_input;
	token_start_i = 0;
	token_len = 0;
	parse_i = 0;
	while (input[parse_i])
	{
		if (is_space(input[parse_i]))
		{
			if (in_quotes[0] || in_quotes[1])
			{
				token_len++;
				parse_i++;
				continue;
			}
			if (token_start_i < parse_i)
			{
				// extract_token(input[parse_i], token_start_i, token_len);
				token_start_i++;
				token_len = 0;
			}
			parse_i++;
		}
		
	}
	shell->nodes = input_to_nodes(shell->latest_input);
	if (!shell->nodes)
		shell_exit(shell, 1);
	// ^ NOTE: Exit here might not even be necessary.
	//         Might be better to always exit inside with specific status
}
