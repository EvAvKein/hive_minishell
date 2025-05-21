/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:53:10 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/21 11:22:17 by ahavu            ###   ########.fr       */
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
	char	**array;

	if (!arr)
		return (NULL);
	array = arr;
	while (length)
		free(array[--length]);
	free(array);
	return (NULL);
}

/**
 * 
 * Frees the provided linked list of nodes -
 * freeing every heap-allocated thing inside them,
 * closing file descriptors for open redirects and deleting heredoc files.
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
		if (node->type == HEREDOC && node->argv[0])
			unlink(node->argv[0]);
		free_2d_arr(node->argv, node->argc);
		fd = node->fd;
		if (fd > 0
			&& fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
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
	free_env_array(shell->ms_envp);
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
