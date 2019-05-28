/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:45:16 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/22 18:22:20 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list *lst;

	if (!(lst = (t_list *)malloc(sizeof(*lst))))
		return (NULL);
	if (!content)
	{
		lst->content = NULL;
		lst->content_size = 0;
	}
	else
	{
		if (!(lst->content = (void*)malloc(content_size)))
		{
			ft_memdel((void**)(&lst));
			return (NULL);
		}
		ft_memcpy(lst->content, content, content_size);
		lst->content_size = content_size;
	}
	lst->next = NULL;
	return (lst);
}
