/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 09:52:30 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/24 15:23:10 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_NEXT_LINE_H
# define SET_NEXT_LINE_H

# include "libft_plus.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FOPEN_MAX
#  define FILES_CAPACITY 10
# endif
# ifndef FILES_CAPACITY
#  define FILES_CAPACITY FOPEN_MAX
# endif
// Mind that 0-2 are taken by default: stdin, stdout, stderr

typedef struct s_line_data
{
	char	**line_ptr;
	char	*line;
	char	*buffer;
	ssize_t	buffer_nl_i;
	int		read_return;
}			t_line_data;

bool	set_next_line(int fd, char **line);
size_t	ft_strlen_until_nl(char *s, ssize_t *nl_i);
char	*ft_strdup_until_nl(char *src, ssize_t *nl_i);
bool	set_str_and_return(char **str_ptr, char *str, bool return_bool);

#endif
