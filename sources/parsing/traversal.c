/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:51:39 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/25 14:48:34 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * Skips the provided pointer for a linked list to its first node.
 * 
 * @param node An address to a `t_node` pointer.
 * 
 */
void	skip_to_last_node(t_node **node)
{
	while (node && *node && (*node)->next)
		*node = (*node)->next;
}

/**
 * 
 * Skips the provided pointer for a linked list to its final node.
 * 
 * @param node An address to a `t_node` pointer.
 * 
 */
void	skip_to_first_node(t_node **node)
{
	while (node && *node && (*node)->prev)
		*node = (*node)->prev;
}
