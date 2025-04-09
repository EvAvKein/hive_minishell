/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:53:57 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:27:44 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	recursive_until_write_last_digit(int n, int fd)
{
	int	digit_char;

	if (n > 9)
		recursive_until_write_last_digit(n / 10, fd);
	digit_char = (n % 10) + '0';
	write(fd, &digit_char, 1);
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	recursive_until_write_last_digit(n, fd);
}
