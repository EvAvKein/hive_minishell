/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:33:50 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/29 18:25:45 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * Write the process ID stored in `shell`
 * into `dest`, incrementing `dest_i` accordingly
 * and skipping `input_i` past the expansion.
 * 
 * @param dest    The destination for writing the PID.
 * 
 * @param dest_i  The first index in `dest` from which to write the PID,
 *                gets incremented past the PID.
 * 
 * @param input_i The input index,
 *                to be incremented past the PID exapnsion.
 * 
 * @returns `true` (for a line-saving conditional chain).
 * 
 */
bool	expand_pid(char *dest, size_t *dest_i, size_t *input_i)
{
	*input_i += 2;
	ft_strlcpy(&dest[*dest_i], get_shell()->pid, 20);
	*dest_i += ft_strlen(get_shell()->pid);
	return (true);
}

/**
 * 
 * Write the digits of exit status stored in `shell`
 * into `dest`, incrementing `dest_i` accordingly
 * and skipping `input_i` past the expansion.
 * 
 * @param dest    The destination for writing the digits.
 * 
 * @param dest_i  The first index in `dest` from which to write the digits,
 *                gets incremented past the digits.
 * 
 * @param input_i The input index,
 *                to be incremented past the exist status expansion.
 * 
 * @returns `true` (for a line-saving conditional chain).
 * 
 */
static bool	expand_exit_status(char *dest, size_t *dest_i, size_t *input_i)
{
	int		status;
	size_t	length;

	*input_i += 2;
	status = get_shell()->last_exit_status;
	length = count_digits(status);
	itoa_to_buf(status, &dest[*dest_i]);
	*dest_i += length;
	return (true);
}

/**
 * 
 * @returns The length of the expanded value for the expansion
 *          starting with the '$' at `expand_start`.
 * 
 * Rejecting in-single-quote expansions is
 * the responsibility of the calling function.
 * 
 */
size_t	expanded_len(char *expand_start)
{
	char	*expansion_value;

	if (expand_start[0] != '$')
		return (0);
	if (!expand_start[1] || is_space(expand_start[1])
		|| is_quote(expand_start[1]) || is_control_flow(expand_start[1]))
		return (1);
	if (expand_start[1] == '$')
		return (ft_strlen(get_shell()->pid));
	if (expand_start[1] == '?')
		return (count_digits(get_shell()->last_exit_status));
	expansion_value = env_value(expand_start + 1);
	if (expansion_value)
		return (ft_strlen(expansion_value));
	return (0);
}

/**
 * 
 * Writes the content of provided expansion in the input's current input index,
 * into the provided destination string at the current destination index.
 * 
 * Increments the values of both indexes past the expansion.
 * 
 * @returns `true` (for a line-saving conditional chain).
 * 
 */
bool	expand_into_dest(t_expand_into_dest_args var)
{
	char	*expansion_value;

	if ((var.input[*var.input_i] != '$' || var.in_quote == '\''))
		return (false);
	if (!var.input[*var.input_i + 1] || is_space(var.input[*var.input_i + 1])
		|| is_quote(var.input[*var.input_i + 1])
		|| is_control_flow(var.input[*var.input_i + 1]))
	{
		(*var.input_i)++;
		var.dest[(*var.dest_i)++] = '$';
		return (true);
	}
	if (var.input[*var.input_i + 1] == '$'
		&& expand_pid(var.dest, var.dest_i, var.input_i))
		return (true);
	if (var.input[*var.input_i + 1] == '?'
		&& expand_exit_status(var.dest, var.dest_i, var.input_i))
		return (true);
	expansion_value = env_value(&var.input[++(*var.input_i)]);
	if (expansion_value)
		*var.dest_i += ft_strlcpy(&var.dest[*var.dest_i],
				expansion_value, ft_strlen(expansion_value) + 1);
	*var.input_i += env_name_len(&var.input[*var.input_i]);
	return (true);
}
