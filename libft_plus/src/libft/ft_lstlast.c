/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:59:01 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/12 13:28:30 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*latest;

	if (!lst)
		return (lst);
	latest = lst;
	while (latest)
	{
		if (!latest->next)
			return (latest);
		latest = latest->next;
	}
	return (latest);
}
