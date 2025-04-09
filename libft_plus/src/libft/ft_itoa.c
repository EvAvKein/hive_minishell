/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:50:49 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 10:17:00 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int		numb;
	size_t	count;

	if (n == 0)
		return (1);
	numb = n;
	count = 0;
	while (numb % 10 || numb / 10)
	{
		count++;
		numb /= 10;
	}
	return (count);
}

static char	*fill_itoa(char *str, int n, int digits, int negative)
{
	int	i;

	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	i = digits + negative - 1;
	while (n % 10 || n / 10)
	{
		str[i--] = (n % 10) + 48;
		if (n < 10)
			break ;
		n /= 10;
	}
	if (negative)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			negative;
	size_t		digits;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n < 0)
	{
		negative = 1;
		n = -n;
	}
	else
		negative = 0;
	digits = count_digits((int) n);
	str = ft_calloc((negative + digits) + 1, sizeof(char));
	if (str == NULL)
		return (NULL);
	return (fill_itoa(str, n, digits, negative));
}
