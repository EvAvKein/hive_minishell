/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:15:41 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/28 14:28:55 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * TODO: Write these docs
 * 
 */
static bool	initialize_dirinfo(t_dirinfo *content, size_t entries)
{
	if (!entries)
	{
		content->arr = NULL;
		return (false);
	}
	content->arr = ft_calloc(entries + 1, sizeof(char *));
	if (!content->arr)
		print_err("parsing: wildcards: ", strerror(ENOMEM));
	return (!!content->arr);
}

/**
 * 
 * Recursively stores another directory entry on the stack
 * until there's no more content (or an error occurs),
 * storing any entries in `content`'s array.
 * 
 * @return Whether there were any directory entries
 *         and memory allocation for the entries array was successful.
 * 
 */
static bool	get_more_dirinfo(t_dirinfo *content, size_t index)
{
	struct dirent	*value;

	value = readdir(content->dir);
	if (!value)
	{
		if (errno)
			print_err("parsing: wildcards: ", strerror(errno));
		return (initialize_dirinfo(content, index));
	}
	if (!ft_strncmp(value->d_name, ".", 2)
		|| !ft_strncmp(value->d_name, "..", 3))
		return (get_more_dirinfo(content, index));
	if (get_more_dirinfo(content, index + 1))
	{
		content->arr[index] = value;
		return (true);
	}
	else
		return (false);
}

/**
 *
 * TODO: Write these docs 
 * 
 */
static void	print_dirinfo()
{
	DIR				*dir;
	t_dirinfo	*storage;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	storage->dir = opendir(cwd);
	free(cwd);
	if (!storage->dir)
		return ;
	errno = 0;
	get_more_dirinfo(storage, 0);
	if (!storage->arr)
	{
		closedir(storage->dir);
		storage->dir = NULL;
	}
}

void	prompt()
{
	if (!parsing->dirinfo.arr)
		printf("no dirinfo\n");
	else
	{
		size_t	i = 0;
		while (parsing->dirinfo.arr[i])
			printf("%s\n", parsing->dirinfo.arr[i++]->d_name);
	}
	printf("\n");
}
