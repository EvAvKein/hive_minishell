/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:25:48 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/25 20:22:31 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	set_start_of_arg(t_str_to_argc_vars *var)
{
	if (!var->in_arg)
	{
		var->in_arg = true;
		if (var->in_operator[0])
			var->in_operator[0] = '\0';
		else
			var->argc++;
	}
}
/**
 * 
 * Counts how many arguments are in the provided string.
 * 
 * @param str The string in which to count the args.
 * 
 * @returns The argument count of the provided string, or `-1` on syntax error.
 * 
 */
int	str_to_argc(char *str, t_str_to_argc_vars var)
{
	while (str[var.i])
	{
		if (is_space(str[var.i]))
		{
			if (var.in_arg && !var.in_quote)
				var.in_arg = false;
			if (!var.in_arg && var.in_quote)
				var.in_quote = '\0';
			var.i++;
			continue ;
		}
		if (!var.in_quote)
		{
			if (str[var.i] == '|')
				break ;
			if (operator_of_c(&str[var.i])
				&& memorize_and_skip_operator(str, &var.i, var.in_operator))
					continue ;
		}
		set_start_of_arg(&var);
		toggle_quote_by_c(&var.in_quote, str[var.i++]);
	}
	if (var.in_operator[0])
		return (-1); /** TODO: Change into syntax error printout */
	return (var.argc);
}

/**
 * 
 * Counts the length of an argument in a given string,
 * omitting quotes that should be parsed away
 * and including spaces within quotes.
 * 
 * @param arg The string for which to calucate the argument length.
 * 
 * @returns The total length, with the aforementioned parsing aspects in mind.
 * 
 */
int	arg_to_len(char *arg)
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
		if (is_space(arg[i]))
		{
			if (in_quote && ++length && ++i)
				continue ;
			return (length);
		}
		if (operator_of_c(&arg[i]) && length--)
			break ;
		if (toggle_quote_by_c(&in_quote, arg[i]))
			length--;
		i++;
	}
	return (length);
}

/**
 * 
 * Copies from `src` to `dest` until the end of the provided arg.
 * 
 * @param dest       The destination for copying.
 *
 * @param src        The source for copying.
 * 
 * @param external_i An address to an external index
 *                   to be incremented past the arg being copied.
 * 
 */
void	arg_cpy(char *dest, char *input, size_t *input_i)
{
	size_t		dest_i;
	char		in_quote;

	dest_i = 0;
	in_quote = '\0';
	while (input[*input_i])
	{
		if (is_space(input[*input_i]))
		{
			if (!in_quote)
				return ;
			dest[dest_i++] = input[(*input_i)++];
			continue ;
		}
		if (!in_quote && operator_of_c(&input[(*input_i)]))
				break ;
		if (!toggle_quote_by_c(&in_quote, input[*input_i]))
			dest[dest_i++] = input[(*input_i)++];
		else
			(*input_i)++;
	}
	return ;
}

/**
 * 
 * Parses through the next valid argument and creates a copy of it.
 * 
 * @returns A copy of the next valid argument (or `NULL` on allocation failure).
 * 
 */
char	*extract_arg(t_parsing *parsing)
{
	size_t	arg_len;
	char	*arg;

	arg_len = arg_to_len(&parsing->input[parsing->i]);
	arg = ft_calloc(1, (arg_len + 1) * (sizeof(char)));
	if (!arg)
		return (NULL);
	arg_cpy(arg, parsing->input, &parsing->i);
	return (arg);
}
