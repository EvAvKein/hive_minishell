/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:25:48 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/17 15:36:11 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * Counts how many arguments are in the provided string.
 * 
 * @param str The string in which to count the args.
 * 
 * @returns The argument count of the provided string.
 * 
 */
static int	str_to_argc(char *str)
{
	t_str_to_argc_vars var;

	var = (t_str_to_argc_vars){.argc = 0, .i = 0,
		.in_quote = '\0', .in_arg = false};
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
		if (operator_of_c(&str[var.i]))
		{
			// printf("found operator %d\n", operator_of_c(&str[var.i]));
			break ;
		}
		if (!var.in_arg && ++var.argc)
			var.in_arg = true;
		toggle_quote_by_c(&var.in_quote, str[var.i++]);
	}
	return (var.argc);
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
void	arg_cpy(char *dest, char *src, size_t *external_i)
{
	t_argv_cpy_vars	var;

	var = (t_argv_cpy_vars){.src_i = 0, .dest_i = 0, .in_quote = '\0'};
	while (src[var.src_i])
	{
		if (is_space(src[var.src_i]))
		{
			if (!var.in_quote)
				return ;
			(*external_i)++;
			dest[var.dest_i++] = src[var.src_i++];
			continue ;
		}
		if (!var.in_quote && operator_of_c(&src[var.src_i]))
				break ;
		if (!toggle_quote_by_c(&var.in_quote, src[var.src_i]))
			dest[var.dest_i++] = src[var.src_i++];
		else
			var.src_i++;
		(*external_i)++;
	}
	return ;
}

/**
 * 
 * Translates the provided string into an array of arguments,
 * allocating the array based on the provided argument count.
 * 
 * @param str  The string to be translated.
 * 
 * @param argc The argument count. ASSUMED TO BE VALID
 *             (i.e. not negative, and a correct count) and is not validated.
 * 
 * @returns An array of the arguments in the `str`
 *          (or `NULL` if allocation failed).
 * 
 */
static char	**str_to_argv(char *str, int argc, size_t *external_i)
{
	t_str_to_argv_vars	var;

	var = (t_str_to_argv_vars){.argv = ft_calloc(argc + 1, sizeof(char *)),
		.argv_i = 0};
	if (!var.argv)
		return (NULL);
	while (var.argv_i < (size_t) argc)
	{
		while (is_space(str[*external_i]))
		{
			(*external_i)++;
			continue ;
		}
		var.arg_len = arg_to_len(&str[*external_i]);
		var.argv[var.argv_i] = ft_calloc(1, (var.arg_len + 1) * (sizeof(char)));
		if (!var.argv[var.argv_i])
			return (free_2d_arr(var.argv, var.argv_i));
		arg_cpy(var.argv[var.argv_i++], &str[*external_i], external_i);
	}
	return (var.argv);
}

/**
 * 
 * TODO: Write these docs
 * 
 */
t_node	*extract_args(char *input, size_t *i)
{
	t_node	*node;

	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL); /** TODO: Print ENOMEM error */
	node->argc = str_to_argc(&input[*i]);
	if (!node->argc)
		return (node);
	node->argv = str_to_argv(input, node->argc, i);
	if (!node->argv)
	{
		free(node);
		return (NULL); /** TODO: Print ENOMEM error */
	}
	node->type = PENDING;
	return (node);
}
