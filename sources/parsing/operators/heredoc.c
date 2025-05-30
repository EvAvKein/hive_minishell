/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:23:50 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/30 10:52:17 by ekeinan          ###   ########.fr       */
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
 * @param dest An pointer to which to assign available (or `NULL`) path.
 * 
 * @returns A heap-allocated path to the next creatable hidden file
 *          (or `NULL` on memory allocation failure).
 *  
 */
static char	*get_available_file_name(char **dest)
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
static void	heredoc_write(int fd, char *input, bool expand)
{
	char	*expansion;
	char	*value;

	if (!expand)
	{
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		return ;
	}
	while (1)
	{
		expansion = ft_strchr(input, '$');
		if (!expansion)
			break ;
		write(fd, input, expansion - input);
		value = env_value(expansion + 1);
		if (value)
			write(fd, value, ft_strlen(value));
		input += (expansion - input) + env_name_len(&expansion[1]) + 1;
	}
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
}

/**
 * 
 * 
 * @param fd     The file descriptor to which to write the heredoc content.
 * 
 * @param expand Whether to expand environment variables written to the heredoc.
 * 
 */
void	heredoc_loop(t_node *node, int fd, bool expand)
{
	char		*input;

	while (1)
	{
		input = readline("heredoc +");
		if (!input || !ft_strncmp(input, node->argv[0], ft_strlen(input)))
		{
			if (input)
				free(input);
			else
				print_err("heredoc: ", "delimited by EOF");
			break ;
		}
		heredoc_write(fd, input, expand);
		free(input);
	}
}

/**
 * 
 * Executes the heredoc for the provided `node`.
 * If successful, replaces `node->argv[0]` from the delimiter to the contents'
 * file path.
 * 
 * @param node   The heredoc node to be executed.
 * 
 * @param expand Whether to expand environment variables written to the heredoc.
 * 
 * @returns Whether heredoc execution was successful.
 * 
 */
bool	execute_heredoc(t_node *node, bool expand)
{
	char		*file_name;
	int			fd;
	const int	heredoc_fd = dup(STDIN_FILENO);

	if (heredoc_fd == -1 && print_err("parsing: ", strerror(errno)))
		return (false);
	if (!get_available_file_name(&file_name))
		return (close(heredoc_fd), false);
	fd = open(file_name, O_CREAT | O_WRONLY, 0644);
	if (fd < 0 && print_err("heredoc: ", strerror(errno)))
		return (close(heredoc_fd), free(file_name), false);
	sigaction(SIGINT,
		&(struct sigaction){.sa_handler = heredoc_sigint_handler}, NULL);
	heredoc_loop(node, fd, expand);
	if ((close(fd) < 0 || dup2(heredoc_fd, STDIN_FILENO) < 0)
		&& (!get_shell()->heredoc_aborted || get_shell()->heredoc_aborted--))
		return (close(heredoc_fd), free(file_name), false);
	sigaction(SIGINT,
		&(struct sigaction){.sa_sigaction = sigint_handler}, NULL);
	close(heredoc_fd);
	free(node->argv[0]);
	node->argv[0] = file_name;
	if (get_shell()->heredoc_aborted)
		return (--get_shell()->heredoc_aborted);
	return (!!node->argv[0]);
}
