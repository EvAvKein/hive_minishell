/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:53:10 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/23 08:37:25 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @param arr    An array of pointers to be freed, also freeing the array itself
 *               (basically `void **`, the single-pointer type is misleading
 *               but necessary).
 * 
 * @param length The amount of individual allocations inside the provided `arr`.
 * 
 * @returns `NULL` (for external line-saving reason, due to Norminette).
 * 
 */
void	*free_2d_arr(void *arr, size_t length)
{
	char **array;

	array = arr;
	while (length)
		free(array[--length]);
	free(array);
	return (NULL);
}

/**
 * 
 * Frees the provided linked list of nodes
 * (and every heap-allocated thing inside them).
 * 
 * @returns `NULL` (for external line-saving reason, due to Norminette).
 * 
 */
void	*free_nodes(t_node *node)
{
	t_node	*next;

	while (node)
	{
		next = node->next;
		free_2d_arr(node->argv, node->argc);
		free(node);
		node = next;
	}
	return (NULL);
}

/**
 * 
 * Frees all allocations in the provided `shell`.
 * 
 */
void	shell_cleanup(t_shell *shell)
{
	free_nodes(shell->nodes);
}

/**
 * 
 * Frees all allocations in the provided `shell`
 * and exit the program with the provided `exit_status`.
 * 
 */
void	shell_exit(t_shell *shell, int exit_status)
{
	shell_cleanup(shell);
	exit(exit_status);
}
