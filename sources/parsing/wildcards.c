/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 17:59:57 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/27 20:57:47 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_dircontent
{
	DIR				*dir;
	struct dirent	**arr;
}	t_dircontent;

static bool	initialize_dircontent(
	t_dircontent *content, size_t depth)
{
	content->arr = ft_calloc(depth + 1, sizeof(char *));
	return (!!content->arr);
}

static bool	get_more_dircontent(t_dircontent *content, size_t depth)
{
	struct dirent	*value;

	value = readdir(content->dir);
	if (errno)
		return (false);
	if (!value)
		return (initialize_dircontent(content, depth));
	if (get_more_dircontent(content, depth + 1))
	{
		content->arr[depth - 1] = value;
		return (true);
	}
	else
	{
		free(value);
		return (false);
	}
}

/**
 * 
 * On success, `errno` will be reset to 0
 * (as that's required for detecting `readdir()` errors).
 * 
 * @returns A heap-allocated array of strings naming all files and directories
 *          at the current directory
 *          (or `NULL` on directory access or memory allocation failure).
 * 
 */
struct dirent	**get_dircontent()
{
	t_dircontent	content;
	char			*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	content.dir = opendir(cwd);
	free(cwd);
	if (!content.dir)
		return (NULL);
	errno = 0;
	get_more_dircontent(&content, 1);
	closedir(content.dir);
	return (content.arr);
}
