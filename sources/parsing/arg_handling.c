/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:25:48 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/14 17:49:12 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static inline void	set_start_of_arg(t_str_to_argc_vars *var)
{
	if (!var->in_arg)
	{
		var->in_arg = true;
		if (var->redirect[0])
			var->redirect[0] = '\0';
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
			if (!(var.in_arg && !var.in_quote && var.in_arg--)
				&& !var.in_arg && var.in_quote)
				var.in_quote = '\0';
			var.i++;
			continue ;
		}
		if (!var.in_quote)
		{
			if (str[var.i] == '|')
				break ;
			if (redirect_of_c(&str[var.i])
				&& memorize_and_skip_redirect(str, &var.i, var.redirect))
					continue ;
		}
		set_start_of_arg(&var);
		toggle_quote_by_c(&var.in_quote, str[var.i++]);
	}
	if (var.redirect[0]
		&& print_err("syntax error: ambiguous redirect: ", var.redirect))
		return (-1);
	return (var.argc);
}

/**
 * 
 * Counts the length of an argument in a given string,
 * accounting for quotes and env expansions.
 * 
 * @param arg The string for which to calucate the argument length.
 * 
 * @returns The total length, with the aforementioned parsing aspects in mind.
 * 
 */
int	arg_to_len(t_shell *shell, char *arg)
{
	t_arg_to_len_vars var;
	
	var = (t_arg_to_len_vars){.i = 0, .length = 0, .in_quote = '\0'};
	while (arg[var.i])
	{
		var.length++;
		if (is_space(arg[var.i]))
		{
			if (var.in_quote && ++var.i)
				continue ;
			return (var.length);
		}
		if (arg[var.i] == '$' && var.in_quote != '\'')
		{
			var.length += expanded_len(shell, &arg[var.i]);
			var.i += env_name_len(&arg[++var.i]);
			continue ;
		}
		if (!var.in_quote && is_control_flow(arg[var.i]) && var.length--)
			break ;
		if (toggle_quote_by_c(&var.in_quote, arg[var.i]))
			var.length--;
		var.i++;
	}
	return (var.length);
}

/**
 * 
 * Copies the argument at the current point in input parsing into `dest`.
 * 
 * @param dest    The destination for copying.
 *
 * @param input   The input being parsed.
 * 
 * @param input_i An address to the current parsing index for the input,
 *                to be incremented past the arg being copied.
 * 
 */
void	arg_cpy(t_shell *shell, char *dest, char *input, size_t *input_i)
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
		if (expand_into_dest((t_expand_into_dest_args){shell, input, input_i,
				in_quote, dest, &dest_i}))
			continue ;
		if (!in_quote && redirect_of_c(&input[(*input_i)]))
				break ;
		if (!toggle_quote_by_c(&in_quote, input[(*input_i)++]))
			dest[dest_i++] = input[(*input_i) - 1];
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
char	*extract_arg(t_shell *shell, t_parsing *parsing)
{
	size_t	arg_len;
	char	*arg;

	arg_len = arg_to_len(shell, &parsing->input[parsing->i]);
	arg = ft_calloc(1, (arg_len + 1) * (sizeof(char)));
	if (!arg)
	{
		print_err("parsing: ", strerror(ENOMEM));
		return (NULL);
	}
	arg_cpy(shell, arg, parsing->input, &parsing->i);
	return (arg);
}
