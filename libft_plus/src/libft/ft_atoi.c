/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:10:02 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:31:31 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	size_t	str_i;
	int		number;
	int		is_negative;

	str_i = 0;
	number = 0;
	is_negative = 0;
	while (nptr[str_i] == ' ' || ((nptr[str_i] >= 9) && (nptr[str_i] <= 13)))
		str_i++;
	if (nptr[str_i] == '-' || nptr[str_i] == '+')
	{
		if (nptr[str_i] == '-')
			is_negative = 1;
		str_i++;
	}
	while (nptr[str_i] >= '0' && nptr[str_i] <= '9')
		number = (number * 10) + (nptr[str_i++] - 48);
	if (is_negative)
		number = 0 - number;
	return (number);
}
