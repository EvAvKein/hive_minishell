/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:39:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/15 08:39:56by ekeinan          ###   ########.fr       */
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
 */
static int	str_to_argc(char *str)
{
	int		argc;
	size_t	i;
	char	in_quote;
	bool	in_arg;

	argc = 0;
	i = 0;
	in_quote = '\0';
	in_arg = false;
	while (str[i])
	{
		if (is_space(str[i]))
		{
			if (in_arg && !in_quote)
				in_arg = false;
			if (!in_arg && in_quote)
				in_quote = '\0';
			i++;
			continue ;
		}
		if (!in_arg && ++argc)
			in_arg = true;
		toggle_quote_by_c(&in_quote, str[i++]);
	}
	return (argc);
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
	size_t		src_i;
	size_t		dest_i;
	char		in_quote;

	src_i = 0;
	dest_i = 0;
	in_quote = '\0';
	while (src[src_i])
	{
		if (is_space(src[src_i]))
		{
			if (!in_quote)
				return ;
			(*external_i)++;
			dest[dest_i++] = src[src_i++];
			continue ;
		}
		if (!toggle_quote_by_c(&in_quote, src[src_i]))
			dest[dest_i++] = src[src_i++];
		else
			src_i++;
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
static char	**str_to_argv(char *str, int argc)
{
	char	**argv;
	int		argv_i;
	size_t	arg_len;
	size_t	str_i;

	argv = ft_calloc(argc + 1, sizeof(char *));
	if (!argv)
		return (NULL);
	argv_i = 0;
	str_i = 0;
	while (argv_i < argc)
	{
		while (is_space(str[str_i]))
		{
			str_i++;
			continue ;
		}
		arg_len = arg_to_len(&str[str_i]);
		argv[argv_i] = ft_calloc(1, arg_len * (sizeof(char) + 1));
		if (!argv[argv_i])
			return (free_2d_arr(argv, argv_i));
		arg_cpy(argv[argv_i++], &str[str_i], &str_i);
	}
	return (argv);
}

/**
 * 
 * Parses the user input stored in `shell`: Storing the parsed output inside
 * `shell` on success, or exiting the program if encountering a parsing issue.
 * 
 * @param shell The address of the initialized shell struct,
 *              from which to get the user input
 *              and in which to store the parsed output.
 * 
 */
void	parsing(t_shell *shell)
{
	t_node *node;
	
	int	argc = str_to_argc(shell->latest_input);
	char **argv = str_to_argv(shell->latest_input, argc);
	if (!argv)
		return ;
	node = ft_calloc(1, sizeof(t_node));
	if (!node)
	{
		free_2d_arr(argv, argc);
		return ;
	}
	*node = (t_node){
		.type = COMMAND,
		.argc = argc,
		.argv = argv,
		.next = NULL
	};
	shell->nodes = node;
}
