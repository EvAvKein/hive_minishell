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
 * TODO: Write these docs
 * 
 */
static	bool is_invalid_identifier(char c)
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
 * TODO: Write these docs
 * 
 * Rejecting in-single-quote expansions is the responsibility of the calling func.
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
	{
		/** TODO: Handle exit code char counting */
		return (1);
	}
	expansion_value = env_value(shell, expand_start + 1);
	if (expansion_value)
		return (ft_strlen(expansion_value));
	return (0);
}

/**
 * 
 * TODO: Write these docs
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
	if (var.input[*var.input_i + 1] == '?')
	{
		/** TODO: Handle exit code expansion (mallocless itoa into dest) */
		return (true);
	}
	expansion_value = env_value(var.shell, &var.input[++(*var.input_i)]);
	if (expansion_value)
		ft_strlcpy(var.dest, expansion_value, ft_strlen(expansion_value));
	*var.input_i += env_name_len(&var.input[*var.input_i], false);
	return (true);
}
