/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 14:15:41 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/29 16:20:10 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * Creates an strings based on `info`'s string length and `MINI_LS_LIMIT`,
 * placing it (or `NULL` on memory allocation failure) in `info`.
 * 
 * @returns Whether an ls string was successfully allocated.
 * 
 */
static bool	init_ls_str(t_mini_ls *info)
{
	if (info->strlen >= MINI_LS_LIMIT)
	{
		info->strlen += 4;
		info->str = ft_calloc(info->strlen + 1, sizeof(char));
		if (info->str)
			ft_strlcpy(&info->str[info->strlen - 4], " ...", 5);
		else
			print_err("parsing: wildcards: ", strerror(ENOMEM));
		info->i = info->strlen - 4;
	}
	else
	{
		info->str = ft_calloc(info->strlen + 1, sizeof(char));
		if (!info->str)
			print_err("parsing: wildcards: ", strerror(ENOMEM));
		info->i = info->strlen;
	}
	return (!!info->str);
}

/**
 * 
 * Writes the provided `value` into `info`'s string behind `info`'s index.
 * 
 */
static void	write_to_ls_str(t_mini_ls *info, char *value)
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
static bool get_more_ls(t_mini_ls *info)
{
	struct dirent	*value;

	value = readdir(info->dir);
	if (!value || info->strlen >= MINI_LS_LIMIT)
		return (init_ls_str(info));
	if (value->d_name[0] == '.')
		return (get_more_ls(info));
	info->strlen += !!info->strlen + ft_strlen(value->d_name);
	if (get_more_ls(info))
	{
		write_to_ls_str(info, value->d_name);
		return (true);
	}
	else
		return (false);
}

/**
 *
 * Prints the files in the current directory (or an error text).
 * 
 */
static void	mini_ls()
{
	t_mini_ls	info;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return ;
	ft_bzero(&info, sizeof(t_mini_ls));
	info.dir = opendir(cwd);
	free(cwd);
	if (!info.dir)
		return ;
	errno = 0;
	get_more_ls(&info);
	closedir(info.dir);
	if (info.str)
	{
		printf("\x1b[38;5;243m%s\x1b[0m\n", info.str);
		free(info.str);
	}
	else if (errno)
		print_err("auto ls: ", strerror(errno));
	else
		printf("\x1b[38;5;243m%s\x1b[0m\n", "[NO FILES IN CWD]");
}

/**
 * 
 * Prints the shell's full prompt
 * (prepended by the files in the current directory if that setting is enabled).
 * 
 * @returns The `readline` string - the user's input to the prompt.
 * 
 */
char	*shell_prompt()
{
	char	*line;
	char	*prompt;
	char	*path;
	bool	free_path;

	if (MINI_LS)
		mini_ls();
	path = get_shell()->working_dir;
	free_path = false;
	if (!path && ++free_path)
		path = getcwd(NULL, 0);
	if (path)
	{
		prompt = str_arr_join((char *[4]){
			(char *)PROMPT_START, path, (char *)PROMPT_END, NULL});
		if (free_path)
			free(path);
		if (prompt)
		{
			line = readline(prompt);
			return (free(prompt), line);
		}
	}
	return (readline(PROMPT_START PROMPT_PATH_PLACEHOLDER PROMPT_END));
}
