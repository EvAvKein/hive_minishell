/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:37:30 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/12 13:33:22 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_infile(t_node *current)
{
	if (dup2(current->fd, STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		return (1);
	}
	close(current->fd);
	current->fd = -1;
	return (0);
}

int	handle_outfile(t_node *current)
{
	current->fd = open(current->argv[0], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (current->fd == -1)
	{
		perror("fd failed");
		return (1);
	}
	else if (dup2(current->fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		return (1);
	}
	close(current->fd);
	current->fd = -1;
	return (0);
}

int	handle_appendfile(t_node *current)
{
	current->fd = open(current->argv[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (current->fd == -1)
	{
		perror("fd failed");
		return (1);
	}
	else if (dup2(current->fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		return (1);
	}
	close(current->fd);
	current->fd = -1;
	return (0);
}

int	count_redirections(t_node *head)
{
	t_node	*tmp;
	int		count;
	
	tmp = head;
	count = 0;
	while (tmp->next && tmp->next != head)
	{
		if (tmp->type == INFILE || tmp->type == OUTFILE || tmp->type == APPENDFILE)
			count++;
		tmp = tmp->next;
	}
	if (tmp->type == INFILE || tmp->type == OUTFILE || tmp->type == APPENDFILE)
		count++;
	return (count);
}

