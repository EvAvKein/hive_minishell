/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:37:30 by ahavu             #+#    #+#             */
/*   Updated: 2025/05/06 15:05:38 by ahavu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("fd failed");
		return (1);
	}
	else if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2 failed");
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_outfile(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("fd failed");
		return (1);
	}
	else if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_appendfile(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("fd failed");
		return (1);
	}
	else if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2 failed");
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_outfiles(t_node *current)
{
	if (current->next->type == OUTFILE)
	{
		if (handle_outfile(current->next->argv[0]) == 1)
			return (1);
	}
	if (current->next->type == APPENDFILE)
	{
		if (handle_appendfile(current->next->argv[0]) == 1)
			return (1);
	}
	return (0);
}
