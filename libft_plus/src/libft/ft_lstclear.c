/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekeinan <ekeinan@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:17:26 by ekeinan           #+#    #+#             */
/*   Updated: 2024/11/12 13:25:58 by ekeinan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*following;

	if (!lst || !*lst || !del)
		return ;
	current = *lst;
	while (current)
	{
		following = current->next;
		ft_lstdelone(current, del);
		current = following;
	}
	*lst = NULL;
}
