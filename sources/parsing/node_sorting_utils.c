/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_sorting_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:17:31 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/19 11:21:58 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * Counts how many infile/heredoc nodes and outfile/appendfile nodes are in the
 * segment being sorted, storing that information back in the provided `
 * sort`.
 * 
 */
void	count_segment_nodes(t_parsing *parsing, t_node_sort *sort)
{
	size_t	node_i_from_end;

	node_i_from_end = 0;
	while (node_i_from_end < parsing->midparse_nodes)
	{
		if (sort->node->type == INFILE || sort->node->type == HEREDOC)
			sort->infile_count++;
		if (sort->node->type == OUTFILE || sort->node->type == APPENDFILE)
			sort->outfile_count++;
		if (!sort->node->prev
			|| sort->node->prev == parsing->node_before_command)
			break ;
		node_i_from_end++;
		sort->node = sort->node->prev;
	}
}

/**
 * 
 * Collect the current segment's nodes based on the counts in `sort
 * `, creating redirection arrays in the struct and assigning the command node.
 * 
 * @returns Whether the collection (with its array allocations) was successful.
 * 
 */
bool	collect_segment_nodes(t_node_sort *sort)
{
	sort->infile_arr = ft_calloc(sort->infile_count + 1, sizeof(t_node *));
	if (!sort->infile_arr
		&& print_err("parsing: ", strerror(ENOMEM)))
		return (false);
	sort->outfile_arr = ft_calloc(sort->outfile_count + 1, sizeof(t_node *));
	if (!sort->outfile_arr)
	{
		print_err("parsing: ", strerror(ENOMEM));
		free(sort->infile_arr);
		return (false);
	}
	while (sort->node)
	{
		if (sort->node->type == INFILE || sort->node->type == HEREDOC)
			sort->infile_arr[--sort->infile_count] = sort->node;
		else if (sort->node->type == OUTFILE || sort->node->type == APPENDFILE)
			sort->outfile_arr[--sort->outfile_count] = sort->node;
		else if (sort->node->type == COMMAND)
			sort->command_node = sort->node;
		sort->node = sort->node->next;
	}
	return (true);
}

/**
 * 
 * Converts the provided array of collected nodes: Connecting the nodes,
 * returning them as a linked list, and resetting the array's pointer to `NULL`.
 *
 * @param nodes_arr A pointer to an array of nodes.
 * 
 * @returns A linked list of the nodes,
 *          or `NULL` if there were no nodes in the array.
 *  
 */
t_node	*link_collected_nodes(t_node ***nodes_arr, size_t i)
{
	t_node	*linked_list;

	if ((*nodes_arr)[i])
	{
		set_prev_and_next((*nodes_arr)[i], NULL, NULL);
		linked_list = (*nodes_arr)[i++];
	}
	else
	{
		free(*nodes_arr);
		*nodes_arr = NULL;
		return (NULL);
	}
	while ((*nodes_arr)[i])
	{
		linked_list->prev = (*nodes_arr)[i];
		set_prev_and_next((*nodes_arr)[i], NULL, linked_list);
		linked_list = (*nodes_arr)[i++];
	}
	free(*nodes_arr);
	*nodes_arr = NULL;
	return (linked_list);
}

/**
 * 
 * During the `reattach_node` process, prepends the `reattach` content to
 * `append` and update `reattach->prev_node` to be the last node in the list.
 * 
 * @param append The node(s) to be appended on top of what's in `reattach`.
 * 
 */
static void	prepend_and_update_prev_node(
	t_node_sort_reattach *reattach, t_node *append)
{
	append->prev = reattach->prev_node;
	if (reattach->prev_node)
		reattach->prev_node->next = append;
	else
		reattach->prev_node = append;
	skip_to_last_node(&reattach->prev_node);
}

/**
 * 
 * Attaches the infile, command, and outfile nodes (in that order)
 * in `reattach`, with the starrt of this linked list assigned to `
 * reattach->start`.
 * 
 */
void	reattach_nodes(t_parsing *parsing, t_node_sort_reattach *reattach)
{
	if (reattach->infiles)
	{
		reattach->start = reattach->infiles;
		prepend_and_update_prev_node(reattach, reattach->infiles);
	}
	if (parsing->command_node)
	{
		set_prev_and_next(parsing->command_node, NULL, NULL);
		if (!reattach->start)
			reattach->start = parsing->command_node;
		prepend_and_update_prev_node(reattach, parsing->command_node);
	}
	if (reattach->outfiles)
	{
		if (!reattach->start)
			reattach->start = reattach->outfiles;
		prepend_and_update_prev_node(reattach, reattach->outfiles);
	}
}
