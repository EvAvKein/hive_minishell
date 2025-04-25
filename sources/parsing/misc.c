/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 08:06:37 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/23 15:22:21 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * Checks whether the character `c` in an opening/closing quote based on
 * `containing_quote`, toggling `containing_quote` accordingly
 * 
 * @param containing_quote An address to the type of the current opening quote
 *                         (`"`, `'`, or `\0`), to be potentially toggled.
 * 
 * @param c                The character being evaluated
 *                         to check whether `containing_quote` should be
 *                         toggled (if it's an opening/closing quote)
 *                         or not (if it's any other character).
 * 
 * @returns Whether `containing_quote` was toggled.
 * 
 */
bool	toggle_quote_by_c(char *containing_quote, char c)
{
	if (c == *containing_quote)
	{
		*containing_quote = '\0';
		return (true);
	}
	else if (!*containing_quote && (c == '\'' || c == '"'))
	{
		*containing_quote = c;
		return (true);
	}
	return (false);
}

/**
 * 
 * TODO: Write these docs
 * 
 */
void	skip_spaces(t_parsing *parsing)
{
	while (is_space(parsing->input[parsing->i]))
		parsing->i++;
}

/**
 * 
 * TODO: Write these docs
 * 
 */
void	set_prev_and_next(t_node *node, t_node *new_prev, t_node *new_next)
{
	node->prev = new_prev;
	node->next = new_next;
}
