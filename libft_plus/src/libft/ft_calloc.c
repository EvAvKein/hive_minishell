/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:11:53 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:21:50 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	bytes;

	if (!size || !nmemb)
		return (malloc(0));
	bytes = nmemb * size;
	if (bytes / nmemb != size)
		return (NULL);
	arr = malloc(bytes);
	if (!arr)
		return (NULL);
	ft_bzero(arr, bytes);
	return (arr);
}
