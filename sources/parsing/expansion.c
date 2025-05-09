/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 09:33:50 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/07 12:33:04 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @returns The digit length of the exit code stored at `shell`.
 * 
 */
size_t	exit_digits_len(t_shell *shell)
{
	unsigned int	status;
	size_t			length;

	status = shell->last_exit_status;
	length = 0;
	while (status % 10 || status / 10)
	{
		length++;
		status /= 10;
	}
	return (length);
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
 * @returns `true` (for a line-saving conditional chain)
 * 
 */
static bool	expand_exit_status(
	t_shell *shell, char *dest, size_t *dest_i, size_t *input_i)
{
	unsigned int	status;
	size_t			length;
	size_t			i;

	*input_i += 2;
	status = shell->last_exit_status;
	if (status == 0)
	{
		dest[(*dest_i)++] = '0';
		return (true);
	}
	length = exit_digits_len(shell);
	i = length - 1;
	while (i >= 0)
	{
		dest[(*dest_i) + i--] = (status % 10) + '0';
		if (status < 10)
			break ;
		status /= 10;
	}
	*dest_i += length;
	return (true);
}

/**
 * 
 * @returns Whether the provided character is an invalid identifier
 *          (e.g. whether it serves as a terminator for expansion names).
 * 
 */
static bool	is_invalid_identifier(char c)
{
	const char	identifiers[] = {'\'', '"', '<', '>', '|', '$', '\0'};
	size_t		i;

	i = 0;
	while (identifiers[i])
		if (identifiers[i++] == c)
			return (true);
	return (false);	
}

/**
 * 
 * @returns The length of the expanded value for the expansion
 *          starting with the '$' at `expand_start`.
 * 
 * Rejecting in-single-quote expansions is
 * the responsibility of the calling func.
 * 
 */
size_t	expanded_len(t_shell *shell, char *expand_start)
{
	char	*expansion_value;

	if (!expand_start[0] || expand_start[0] != '$')
		return (0);
	if (!expand_start[1] ||
		is_space(expand_start[1]) || is_invalid_identifier(expand_start[1]))
		return (1);
	if (expand_start[1] == '?')
		return (exit_digits_len(shell));
	expansion_value = env_value(shell, expand_start + 1);
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
 * @returns `true` (for a line-saving conditional chain)
 * 
 */
bool	expand_into_dest(t_expand_into_dest_args var)
{
	char	*expansion_value;

	if (!var.input[*var.input_i] ||
		(var.input[*var.input_i] != '$' || var.in_quote == '\''))
		return (false);
	if (!var.input[*var.input_i + 1] || is_space(var.input[*var.input_i + 1])
		|| is_invalid_identifier(var.input[*var.input_i + 1]))
	{
		var.dest[(*var.dest_i)++] = '$';
		(*var.input_i)++;
		return (true);
	}
	if (var.input[*var.input_i + 1] == '?'
		&& expand_exit_status(var.shell, var.dest, var.dest_i, var.input_i))
		return (true);
	expansion_value = env_value(var.shell, &var.input[++(*var.input_i)]);
	if (expansion_value)
	{
		ft_strlcpy(&var.dest[*var.dest_i],
			expansion_value, ft_strlen(expansion_value) + 1);
		*var.dest_i += ft_strlen(expansion_value);
	}
	*var.input_i += env_name_len(&var.input[*var.input_i], false);
	return (true);
}
