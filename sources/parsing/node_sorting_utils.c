/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_sorting_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:17:31 by ekeinan           #+#    #+#             */
/*   Updated: 2025/04/24 20:25:50 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * TODO: Write these docs
 * 
 */
void count_segment_nodes(t_parsing *parsing, t_node_sort *sort)
{
	size_t	node_i_from_end;
	
	node_i_from_end = 0;
	while (node_i_from_end < parsing->midparse_nodes)
	{
		if (sort->node->type == INFILE || sort->node->type == HEREDOC)
			sort->infile_count++;
		if (sort->node->type == OUTFILE || sort->node->type == APPENDFILE)
			sort->outfile_count++;
		if (!sort->node->prev)
			break ;
		node_i_from_end++;
		sort->node = sort->node->prev;
	}
}

/**
 * 
 * TODO: Write these docs
 * 
 */
bool collect_segment_nodes(t_node_sort *sort)
{
	sort->infile_arr = ft_calloc(sort->infile_count + 1, sizeof(t_node *));
	if (!sort->infile_arr)
		return (false); /** TODO: Print ENOMEM ERROR */
	sort->outfile_arr = ft_calloc(sort->outfile_count + 1, sizeof(t_node *));
	if (!sort->outfile_arr)
	{
		free(sort->infile_arr); /** TODO: Print ENOMEM ERROR */
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
 * TODO: Write these docs
 *
 * @param nodes_arr A pointer to an array of nodes.
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
 * TODO: Write these docs
 * 
 */
static void	append_and_update_prev_node(
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
 * TODO: Write these docs
 * 
 */
void	reattach_nodes(t_parsing *parsing, t_node_sort_reattach *reattach)
{
	if (reattach->infiles)
	{
		reattach->start = reattach->infiles;
		append_and_update_prev_node(reattach, reattach->infiles);
	}
	if (parsing->command_node)
	{
		set_prev_and_next(parsing->command_node, NULL, NULL);
		if (!reattach->start)
			reattach->start = parsing->command_node;
		append_and_update_prev_node(reattach, parsing->command_node);
	}
	if (reattach->outfiles)
	{
		if (!reattach->start)
			reattach->start = reattach->outfiles;
		append_and_update_prev_node(reattach, reattach->outfiles);
	}
}
