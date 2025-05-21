/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 11:18:31 by ekeinan           #+#    #+#             */
/*   Updated: 2025/05/20 20:32:50 by ekeinan          ###   ########.fr       */
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
