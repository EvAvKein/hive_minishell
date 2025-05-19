/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:23:50 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/19 11:24:05 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @returns Whether the parsed delimitered is adjacent to or contains any quote.
 * 
 */
bool	is_delimiter_quoted(t_parsing *parsing)
{
	char	*input;
	size_t	i;

	input = parsing->input;
	i = parsing->i;
	while (input[--i] != '<')
		if (is_quote(input[i]))
			return (true);
	return (false);
}

/**
 * 
 * Increments the character-based number at the end of the provided string.
 * 
 * @param buffer The array in which increment the number
 *               according to its digit characters.
 *               Assumed to contain at least one leading non-space character,
 *               at least one digit,
 *               and assumed to have enough space for all necessary digits.
 * 
 */
void	increment_postfixed_num(char *buffer)
{
	size_t	i;

	i = ft_strlen(buffer) - 1;
	if (buffer[i] < '9')
	{
		buffer[i]++;
		return ;
	}
	while (buffer[i] == '9')
	{
		if (!ft_isdigit(buffer[i - 1]))
		{
			buffer[i++] = '1';
			while (buffer[i])
				buffer[i++] = '0';
			break ;
		}
		buffer[i--] = '0';
	}
	if (!buffer[i])
		buffer[i] = '0';
	else
		buffer[i]++;
}

/**
 * 
 * @returns A heap-allocated (or `NULL`) path to the next creatable hidden file.
 * 
 * @param dest An pointer to which to assign available (or `NULL`) path.
 * 
 * @returns The value asssigned to `dest`.
 *  
 */
char	*get_available_file_name(char **dest)
{
	char	name[35];

	ft_bzero(name, 35);
	if (!access("/tmp", O_DIRECTORY))
	{
		print_err("\"/tmp\" directory is inaccessible for heredoc: ",
			strerror(errno));
		*dest = NULL;
		return (NULL);
	}
	ft_strlcpy(name, "/tmp/.shellGBTQ_heredoc_0", 26);
	while (!access(name, F_OK))
		increment_postfixed_num(name);
	*dest = ft_strdup(name);
	if (!*dest)
		print_err("heredoc: ", strerror(ENOMEM));
	return (*dest);
}

/**
 * 
 * @param fd     The file descriptor in which to write the content of `input`.
 * 
 * @param input  The heredoc line to be written.
 * 
 * @param expand Whether to expand environment variables in the `input`.
 * 
 */
void	heredoc_write(int fd, char *input, bool expand)
{
	char	*expansion;
	char	*value;

	if (!expand)
	{
		write(fd, input, ft_strlen(input));
		return ;
	}
	while (1)
	{
		expansion = ft_strchr(input, '$');
		if (!expansion)
			break ;
		write(fd, input, expansion - input);
		value = env_value(get_shell(), expansion);
		if (value)
			write(fd, value, ft_strlen(value));
		input += (expansion - input) + env_name_len(&expansion[1]) + 1;
	}
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
}

/**
 * 
 * Executes the heredoc for the provided `node`.
 * If successful, replaces `node->argv[0]` from the delimiter to the contents'
 * file path.
 * 
 * @param expand Whether to expand environment variables written to the heredoc.
 * 
 * @returns Whether heredoc execution was successful.
 * 
 */
bool	execute_heredoc(t_node *node, bool expand)
{
	char	*file_name;
	int		fd;
	char	*input;

	if (!get_available_file_name(&file_name))
		return (false);
	fd = open(file_name, O_CREAT | O_WRONLY, 0644);
	if (fd < 0 && print_err("heredoc: ", strerror(errno)))
		return (free(file_name), false);
	while (1)
	{
		input = readline("heredoc +");
		if (!input || !ft_strncmp(input, node->argv[0], ft_strlen(input)))
		{
			if (input)
				free(input);
			break ;
		}
		heredoc_write(fd, input, expand);
		free(input);
	}
	close(fd);
	free(node->argv[0]);
	node->argv[0] = file_name;
	return (!!node->argv[0]);
}
