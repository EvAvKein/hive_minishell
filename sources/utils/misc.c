/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 21:21:54 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/11 17:42:12 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * 
 * @returns The amount of digits in the provided number.
 * 
 */
size_t	count_digits(int num)
{
	size_t	count;

	if (num == 0)
		return (1);
	count = 0;
	while (num % 10 || num / 10)
	{
		count++;
		num /= 10;
	}
	return (count);
}

/**
 * 
 * Writes the digit and sign of the provided number into the provided buffer.
 * 
 * The buffer is assumed to have capacity for at least 12 characters
 * (to fit a negative sign, the 10 digits of INT_MAX, and a null terminator).
 * 
 * @param num The number to be written as a string.
 * 
 * @param buf The buffer/string into which to write the number as characters.
 * 
 * @returns The `buf` param.
 * 
 */
char	*itoa_to_buf(int num, char *buf)
{
	int		i;
	bool	negative;

	if (!buf)
		return (NULL);
	negative = num < 0;
	if (negative)
		num = -num;
	i = count_digits(num) + negative;
	buf[i--] = '\0';
	if (num == 0)
		buf[i] = '0';
	while (num % 10 || num / 10)
	{
		buf[i--] = (num % 10) + 48;
		if (num < 10)
			break ;
		num /= 10;
	}
	if (negative)
		buf[i] = '-';
	return (buf);
}

/**
 * 
 * Writes the current process' ID
 * (or an error indicator on failure)
 * to the provided buffer.
 * 
 * @param buf A buffer for writing the PID or the error indicator,
 *            assumed to have a size of (at least) 20.
 * 
 * @returns The buffer.
 * 
 */
char	*pid_to_buf(char buf[20])
{
	int		fd;
	int		i;
	
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0 || read(fd, buf, 20) < 0)
		ft_strlcpy(buf, "[PID UNAVAILABLE]", 18);
	else
	{
		i = 0;
		while (buf[i] && buf[i] != ' ')
			i++;
		buf[i] = '\0';
	}
	if (fd >= 0)
		close(fd);
	return (buf);
}
