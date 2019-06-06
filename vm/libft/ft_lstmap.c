/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:45:09 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/22 18:22:20 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*lst_new;

	if (!lst || !f)
		return (NULL);
	lst_new = f(lst);
	if (!(lst_new = ft_lstnew(lst_new->content, lst_new->content_size)))
		return (NULL);
	if (lst->next && !(lst_new->next = ft_lstmap(lst->next, f)))
	{
		ft_strdel(lst_new->content);
		lst_new->content = 0;
		free(lst_new);
		lst_new = 0;
		return (NULL);
	}
	return (lst_new);
}
