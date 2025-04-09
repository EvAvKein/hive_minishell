/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2224/11/14 15:00:24 by ekeinan           #+#    #+#             */
/*   Updated: 2025/02/18 10:36:01 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

static void	convert(int fd, char *str, va_list args, long long *print_count)
{
	str++;
	if (!*str)
		increase_print_count(-1, print_count);
	else if (*str == '%')
		increase_print_count(write(fd, "%", 1), print_count);
	else if (*str == 'c')
		print_char(fd, va_arg(args, int), print_count);
	else if (*str == 's')
		print_str(fd, va_arg(args, char *), print_count);
	else if (*str == 'p')
		print_ptr(fd, va_arg(args, uintptr_t), print_count);
	else if (*str == 'd')
		print_int(fd, va_arg(args, int), print_count);
	else if (*str == 'i')
		print_int(fd, va_arg(args, int), print_count);
	else if (*str == 'u')
		print_uint(fd, va_arg(args, unsigned int), print_count);
	else if (*str == 'x')
		print_lowerhex(fd, va_arg(args, unsigned int), print_count);
	else if (*str == 'X')
		print_upperhex(fd, va_arg(args, unsigned int), print_count);
	else
		increase_print_count(write(fd, --str, 2), print_count);
}

static size_t	segment_length(const char *s)
{
	char	*pointer_to_next_conv;

	pointer_to_next_conv = ft_strchr(s, '%');
	if (pointer_to_next_conv)
		return (pointer_to_next_conv - s);
	else
		return (ft_strlen(s));
}

static void	print(int fd, char *format, va_list args, long long	*print_count)
{
	size_t	f_i;
	size_t	cur_seg_len;

	f_i = 0;
	while (format[f_i])
	{
		if (*print_count < 0)
			break ;
		if (format[f_i] == '%')
		{
			convert(fd, &format[f_i], args, print_count);
			f_i += (2 - !format[f_i + 1]);
			continue ;
		}
		cur_seg_len = segment_length(&format[f_i]);
		increase_print_count(write(fd, &format[f_i], cur_seg_len), print_count);
		f_i += cur_seg_len;
	}
}

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list		args;
	long long	print_count;

	if (!format)
		return (-1);
	print_count = 0;
	va_start(args, format);
	print(fd, (char *) format, args, &print_count);
	va_end(args);
	return (print_count);
}
