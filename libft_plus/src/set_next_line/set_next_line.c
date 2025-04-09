/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:26:47 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/18 11:29:57 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_next_line.h"

static void	move_to_start(char *s, size_t start_i)
{
	size_t	s_i;

	if (start_i == 0)
		return ;
	s_i = 0;
	while (s[start_i])
		s[s_i++] = s[start_i++];
	while (s_i < start_i)
		s[s_i++] = '\0';
}

static void	reset_buffer(char *buffer, ssize_t *buffer_nl_i)
{
	if (*buffer_nl_i >= 0)
		move_to_start(buffer, *buffer_nl_i + 1);
	else
		ft_bzero(buffer, BUFFER_SIZE);
}

static bool	init_data(t_line_data *data, char **line_ptr, char *buffer, int fd)
{
	*data = (t_line_data){.line_ptr = line_ptr, .line = NULL,
		.buffer = buffer, .buffer_nl_i = -1};
	if (BUFFER_SIZE < 1 || FILES_CAPACITY < 1
		|| fd > FILES_CAPACITY - 1 || fd < 0)
		return (set_str_and_return(data->line_ptr, NULL, 0));
	if (*data->buffer)
	{
		data->line = ft_strdup_until_nl(data->buffer, &data->buffer_nl_i);
		if (!data->line)
			return (set_str_and_return(data->line_ptr, data->line, 0));
		reset_buffer(data->buffer, &data->buffer_nl_i);
		return (set_str_and_return(data->line_ptr, data->line, 1));
	}
	else
	{
		data->line = malloc(sizeof(char));
		if (!data->line)
			return (set_str_and_return(data->line_ptr, data->line, 0));
		data->line[0] = '\0';
		*line_ptr = data->line;
		return (1);
	}
}

static int	append_to_line(char **line, char *buffer, ssize_t *buffer_nl_i)
{
	size_t	total_len;
	char	*combined;
	size_t	combined_i;
	size_t	i;

	total_len = ft_strlen(*line) + ft_strlen_until_nl(buffer, buffer_nl_i);
	combined = malloc((total_len + 1) * sizeof(char));
	if (!combined)
	{
		free(*line);
		return (0);
	}
	combined_i = 0;
	i = 0;
	while ((*line)[i])
		combined[combined_i++] = (*line)[i++];
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		combined[combined_i++] = buffer[i++];
	if (buffer[i] == '\n')
		combined[combined_i++] = '\n';
	combined[combined_i] = '\0';
	free(*line);
	*line = combined;
	return (1);
}

bool	set_next_line(int fd, char **line_ptr)
{
	static char		buffers[FILES_CAPACITY][BUFFER_SIZE + 1];
	t_line_data		data;

	if (!init_data(&data, line_ptr, buffers[fd], fd))
		return (set_str_and_return(line_ptr, NULL, 0));
	if (data.buffer_nl_i >= 0)
		return (set_str_and_return(line_ptr, data.line, 1));
	while (1)
	{
		if (!buffers[fd][0])
		{
			data.read_return = read(fd, buffers[fd], BUFFER_SIZE);
			if (data.read_return < 0)
				return (set_str_and_return(line_ptr, data.line, 0));
			if (!data.read_return)
				return (set_str_and_return(line_ptr, data.line, 1));
		}
		if (!append_to_line(&data.line, buffers[fd], &data.buffer_nl_i))
			return (set_str_and_return(line_ptr, NULL, 1));
		reset_buffer(buffers[fd], &data.buffer_nl_i);
		if (data.buffer_nl_i >= 0)
			return (set_str_and_return(line_ptr, data.line, 1));
	}
}
