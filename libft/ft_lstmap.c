/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 19:58:40 by nsondag           #+#    #+#             */
/*   Updated: 2018/06/25 14:16:16 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *begin;

	if (!lst)
		return (NULL);
	new = ft_lstnew(f(lst)->content, f(lst)->content_size);
	begin = new;
	while (lst->next)
	{
		lst = lst->next;
		new->next = ft_lstnew(f(lst)->content, f(lst)->content_size);
		new = new->next;
	}
	new->next = NULL;
	return (begin);
}
