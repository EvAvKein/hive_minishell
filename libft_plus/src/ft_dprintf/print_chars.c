/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_chars.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:09:25 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/11 10:50:23 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	print_char(int fd, char c, long long *print_count)
{
	increase_print_count(write(fd, &c, 1), print_count);
}

void	print_str(int fd, char *s, long long *print_count)
{
	if (!s)
	{
		increase_print_count(write(fd, "(null)", 6), print_count);
		return ;
	}
	increase_print_count(write(fd, s, ft_strlen(s)), print_count);
}
