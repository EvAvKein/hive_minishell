/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_to_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 12:47:16 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/09 20:02:10 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/** 
 * 
 * WIP: Currently returns a single node.
 * No space-agnostic tokenizing or input handling just yet
 *
 * TODO: Consider exiting inside on every error.
 *       If doing that, document it here to spare external NULL checks.
 * 
 */
t_node	*input_to_nodes(char *input)
{
	t_node *node;
	int		argc;
	int		argv_i;
	
	node = ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = COMMAND;
	node->argv = ft_split(input, ' ');
	if (!node->argv)
	{
		free(node);
		return (NULL);
	}
	argc = 0;
	argv_i = 0;
	while (node->argv[argv_i++])
		argc++;
	node->next = NULL;
	return (node);
}
