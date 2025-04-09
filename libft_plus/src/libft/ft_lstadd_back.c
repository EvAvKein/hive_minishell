/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:09:28 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/12 13:28:04 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*latest;

	if (!new)
		return ;
	if (!lst || !*lst)
	{
		*lst = new;
		return ;
	}
	latest = *lst;
	while (latest)
	{
		if (!latest->next)
			break ;
		latest = latest->next;
	}
	latest->next = new;
}
