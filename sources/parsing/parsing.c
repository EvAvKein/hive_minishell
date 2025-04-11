/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:39:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/11 17:57:06 by ekeinan          ###   ########.fr       */
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
// static bool	is_skippable_quote(bool in_quotes[2], char *c, bool has_previous)
// {
// 	if (*c == '\'')
// 	{
// 		if (in_quotes[1])
// 			return (false);
// 		if ((has_previous && *(c - 1) != '\'') || in_quotes[0])
// 		{
// 			in_quotes[0] = !in_quotes[0];
// 			return (true);
// 		}
// 	}
// 	if (*c == '"')
// 	{
// 		if (in_quotes[0])
// 			return (false);
// 		if ((has_previous && *(c - 1) != '"') || in_quotes[1])
// 		{
// 			in_quotes[1] = !in_quotes[1];
// 			return (true);
// 		}
// 	}
// 	return (false);
// }

/**
 * 
 *  TODO: Write this doc
 * 
 */
static bool	toggle_quote_by_c(char *containing_quote, char *c)
{
	char chr;

	chr = *c;
	if (chr == *containing_quote)
	{
		printf("found closing quote %c\n", chr);
		*containing_quote = '\0';
		return (true);
	}
	else if (!*containing_quote && (chr == '\'' || chr == '"'))
	{
		printf("found opening quote %c\n", chr);
		*containing_quote = chr;
		return (true);
	}
	// if (!in_arg)
	// {
	// 	printf("not in_arg toggle\n");
	// 	*containing_quote = '\0';
	// }
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
 */
int	arg_len(char *arg, size_t *external_i)
{
	size_t		i;
	size_t		length;
	char		in_quote;

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
				continue ;
			return (length);
		}
		if (toggle_quote_by_c(&in_quote, &arg[i]))
			length--;
		i++;
	}
	return (length);
}

/**
 * 
 *  TODO: Write this doc
 * 
 */
static int	argc_of_input(char *input)
{
	int		argc;
	size_t	i;
	char	in_quote;
	bool	in_arg;

	argc = 0;
	i = 0;
	in_quote = '\0';
	in_arg = false;
	while (input[i])
	{
		if (is_space(input[i]))
		{
			if (in_arg && !in_quote)
			{
				// printf("i %lu: end of quotes\n", i);
				in_arg = false;
			}
			if (!in_arg && in_quote)
				in_quote = '\0';
			// printf("i %lu: space\n", i);
			i++;
			continue ;
		}
		if (!in_arg)
		{
			// printf("i %lu: new arg\n", i);
			argc++;
			in_arg = true;
		}
		toggle_quote_by_c(&in_quote, &input[i]);
		i++;
	}
	return (argc);
}
void	parsing(t_shell *shell)
{
	int	argc = argc_of_input(shell->latest_input);
	printf("argc: %d\n", argc);
	shell->nodes = input_to_nodes(shell->latest_input);
	if (!shell->nodes)
		shell_exit(shell, 1);
	// ^ NOTE: Exit here might not even be necessary.
	//         Might be better to always exit inside with specific status
}
