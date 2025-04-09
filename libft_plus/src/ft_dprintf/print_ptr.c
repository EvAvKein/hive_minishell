/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:23:06 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/11 12:47:32 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	print_ptr(int fd, uintptr_t ptr_as_num, long long *print_count)
{
	if (!ptr_as_num)
	{
		increase_print_count(write(fd, "(nil)", 5), print_count);
		return ;
	}
	increase_print_count(write(fd, "0x", 2), print_count);
	if (*print_count < 0)
		return ;
	print_lowerhex(fd, ptr_as_num, print_count);
}
