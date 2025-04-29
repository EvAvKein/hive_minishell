/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahavu <ahavu@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 08:37:30 by ahavu             #+#    #+#             */
/*   Updated: 2025/04/29 11:14:09 by ahavu            ###   ########.fr       */
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

int	apply_redirections(t_node *current)
{
	if (current->type == INFILE)
	{
		handle_infile(current->argv[0]);
		return(1);
	}
	if (current->type == OUTFILE)
	{
		handle_outfile(current->argv[0]);
		return (1);
	}
	if (current->type == APPENDFILE)
	{
		handle_appendfile(current->argv[0]);
		return (1);
	}
	return (0);
}
