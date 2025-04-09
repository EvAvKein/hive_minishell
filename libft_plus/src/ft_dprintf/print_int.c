/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 08:40:17 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/11 12:14:18 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	write_last_digit(int fd, int n, long long *print_count)
{
	char	digit_char;

	if (n > 9)
		write_last_digit(fd, n / 10, print_count);
	if (*print_count < 0)
		return ;
	digit_char = (n % 10) + '0';
	increase_print_count(write(fd, &digit_char, 1), print_count);
}

static void	write_last_udigit(int fd, unsigned int n, long long *print_count)
{
	char	digit_char;

	if (n > 9)
		write_last_digit(fd, n / 10, print_count);
	if (*print_count < 0)
		return ;
	digit_char = (n % 10) + '0';
	increase_print_count(write(fd, &digit_char, 1), print_count);
}

void	print_int(int fd, int n, long long *print_count)
{
	if (n == -2147483648)
	{
		increase_print_count(write(fd, "-2147483648", 11), print_count);
		return ;
	}
	if (n < 0)
	{
		increase_print_count(write(fd, "-", 1), print_count);
		if (*print_count < 0)
			return ;
		n = -n;
	}
	write_last_digit(fd, n, print_count);
}

void	print_uint(int fd, unsigned int n, long long *print_count)
{
	write_last_udigit(fd, n, print_count);
}
