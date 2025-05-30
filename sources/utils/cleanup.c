/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 15:53:10 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/30 09:51:44 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		free_str_arr(node->argv);
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
 * Frees all command-specific allocations in the shell,
 * resetting their variable values in preperation for new command input.
 * 
 */
void	command_cleanup(void)
{
	free_nodes(get_shell()->nodes);
	get_shell()->nodes = NULL;
}

/**
 * 
 * Frees all allocations in the shell.
 * 
 */
void	shell_cleanup(void)
{
	free_str_arr(get_shell()->env);
	get_shell()->env = NULL;
	if (get_shell()->working_dir)
	{
		free(get_shell()->working_dir);
		get_shell()->working_dir = NULL;
	}
	command_cleanup();
}

/**
 * 
 * Frees all allocations in the shell
 * and exit the program with the provided `exit_status`.
 * 
 */
void	shell_exit(int exit_status)
{
	shell_cleanup();
	exit((unsigned char)exit_status);
}
