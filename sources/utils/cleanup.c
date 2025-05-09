/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:53:10 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/30 14:21:51 by ahavu            ###   ########.fr       */
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
	int		fd;

	while (node)
	{
		next = node->next;
		free_2d_arr(node->argv, node->argc);
		fd = node->fd;
		if (fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
			close(node->fd);
		free(node);
		node = next;
	}
	return (NULL);
}

/**
 * 
 * Frees all command-specific allocations in the provided `shell`,
 * resetting their variable values in preperation for new command input.
 * 
 */
void	command_cleanup(t_shell *shell)
{
	free_nodes(shell->nodes);
	shell->nodes = NULL;
}

/**
 * 
 * Frees all allocations in the provided `shell`.
 * 
 */
void	shell_cleanup(t_shell *shell)
{
	command_cleanup(shell);
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
