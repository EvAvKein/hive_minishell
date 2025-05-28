/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:15:41 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/28 21:48:23 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * TODO: Write these docs
 * 
 */
static bool	initialize_dirinfo(t_dirinfo *info)
{
	if (!info->strlen)
	{
		info->str = NULL;
		return (false);
	}
	if (info->strlen >= AUTO_LS_LIMIT)
	{
		info->strlen += 4;
		info->str = ft_calloc(info->strlen + 1, sizeof(char *));
		if (!info->str)
			ft_strlcpy(&info->str[info->strlen - 5], " ...", 5);
		else
			print_err("parsing: wildcards: ", strerror(ENOMEM));
		info->i = info->strlen - 4;
	}
	else
	{
		info->str = ft_calloc(info->strlen + 1, sizeof(char *));
		if (!info->str)
			print_err("parsing: wildcards: ", strerror(ENOMEM));
		info->i = info->strlen;
	}
	return (!!info->str);
}

/**
 * 
 * TODO: Write these docs
 * 
 */
static void	write_to_dirinfo_str(t_dirinfo *info, char *value)
{
	size_t	value_len;

	value_len = ft_strlen(value);
	ft_strlcpy(&info->str[info->i - value_len], value, value_len + 1);
	if (info->i != info->strlen)
		info->str[info->i] = ' ';
	info->i -= value_len + 1;
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
static bool get_more_dirinfo(t_dirinfo *info)
{
	struct dirent	*value;

	value = readdir(info->dir);
	if (!value || info->strlen >= AUTO_LS_LIMIT)
	{
		if (errno)
			print_err("parsing: wildcards: ", strerror(errno));
		return (initialize_dirinfo(info));
	}
	if (!ft_strncmp(value->d_name, ".", 2)
		|| !ft_strncmp(value->d_name, "..", 3))
		return (get_more_dirinfo(info));
	info->strlen += !!info->strlen + ft_strlen(value->d_name);
	if (get_more_dirinfo(info))
	{
		write_to_dirinfo_str(info, value->d_name);
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
static void	mini_ls()
{
	t_dirinfo	info;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	ft_bzero(&info, sizeof(t_dirinfo));
	info.dir = opendir(cwd);
	free(cwd);
	if (!info.dir)
		return ;
	errno = 0;
	get_more_dirinfo(&info);
	closedir(info.dir);
	if (info.str)
	{
		printf("\033[2;33m%s\033[0m\n", info.str);
		free(info.str);
	}
	else
		printf("woo\n");
}

/**
 * 
 * TODO: Write these docs
 * 
 */
char	*shell_prompt()
{
	// char	*line;
	// char	*prompt;
	// char	*path;
	// bool	path_allocated;

	mini_ls();

	//path = get_shell();
	//if ()
	
	return (readline(PROMPT_START PROMPT_PATH_PLACEHOLDER PROMPT_END));
}
