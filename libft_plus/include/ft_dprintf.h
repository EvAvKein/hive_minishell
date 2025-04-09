/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:09:59 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/24 15:23:32 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include "libft_plus.h"

// Print to given file descripter, based on template and converted values
int		ft_dprintf(int fd, const char *format, ...);

// Increase print count *unless* increase is/was negative
void	increase_print_count(long long increase, long long *print_count);

// Print a character and increase print count
void	print_char(int fd, char c, long long *print_count);

// Print a string and increase print count
void	print_str(int fd, char *s, long long *print_count);

// Print a pointer address and increase print count
void	print_ptr(int fd, uintptr_t ptr_as_num, long long *print_count);

// Print an integer and increase print count
void	print_int(int fd, int n, long long *print_count);

// Print an unsigned integer and increase print count
void	print_uint(int fd, unsigned int n, long long *print_count);

// Print a lowercase hexadecimal by number and increase print count
void	print_lowerhex(int fd, unsigned long long n, long long *print_count);

// Print a uppercase hexadecimal by number and increase print count
void	print_upperhex(int fd, unsigned long long n, long long *print_count);

#endif
