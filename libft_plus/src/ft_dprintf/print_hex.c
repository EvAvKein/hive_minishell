/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:16:39 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/11 13:07:25 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	print_upperhex(int fd, unsigned long long n, long long *print_count)
{
	char	chr;

	if (n > 15)
	{
		print_upperhex(fd, n / 16, print_count);
		if (*print_count < 0)
			return ;
		n %= 16;
	}
	if (n < 10)
		chr = (n % 10) + '0';
	else
		chr = (n % 10) + 'A';
	increase_print_count(write(fd, &chr, 1), print_count);
}

void	print_lowerhex(int fd, unsigned long long n, long long *print_count)
{
	char	chr;

	if (n > 15)
	{
		print_lowerhex(fd, n / 16, print_count);
		if (*print_count < 0)
			return ;
		n %= 16;
	}
	if (n < 10)
		chr = (n % 10) + '0';
	else
		chr = (n % 10) + 'a';
	increase_print_count(write(fd, &chr, 1), print_count);
}
