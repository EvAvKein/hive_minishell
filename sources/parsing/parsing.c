/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 10:57:48 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/17 18:27:28 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * TODO: Either remove, or move to "verbose" printing file/directory
 * 
 */
void	print_nodes(t_node *node)
{
	// size_t	count = 1;
	int		i;

	while (node)
	{
		// printf(" node %lu\n", count);
		printf("  argc: %d\n", node->argc);
		if (!node->argc)
		{
			node = node->next;
			continue ;
		}
		i = 0;
		while (node->argv[i])
		{
			printf("  argv i-%d: \"%s\"\n", i, node->argv[i]);
			i++;
		}
		node = node->next;
	}
}

/**
 * 
 * Parses the user input stored in `shell`, storing the parsed output inside
 * `shell` on success.
 * 
 * @param shell The address of the initialized shell struct,
 *              from which to get the user input
 *              and in which to store the parsed output.
 * 
 * @returns Whether the parsed input is valid.
 * 
 */
bool	parsing(t_shell *shell)
{
	t_node	*node;
	t_node	**node_next;
	char	*input;
	size_t	i;

	i = 0;
	input = shell->latest_input;
	node_next = &shell->nodes;
	while (input[i])
	{
		if (is_space(input[i]) && ++i)
			continue ;
		if (!handle_operator(shell, node, &i))
			return (false);
		node = extract_args(input, &i);
		if (!node)
			return (false);
		*node_next = node;
		while (*node_next)
		{
			print_nodes(node);
			node_next = &((*node_next)->next);
		}
	}
	return (true);
}
