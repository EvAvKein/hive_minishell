/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:35:12 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/22 16:25:48 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*latest;
	size_t	count;

	if (!lst)
		return (0);
	latest = lst;
	count = 1;
	while (latest)
	{
		if (!latest->next)
			break ;
		latest = latest->next;
		count++;
	}
	return (count);
}
