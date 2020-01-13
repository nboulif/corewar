/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/10 13:23:28 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/17 09:39:33 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_l;

	new_l = (t_list *)ft_memalloc(sizeof(t_list));
	if (new_l == NULL)
		return (NULL);
	new_l->next = NULL;
	if (content == NULL || content_size == 0)
	{
		new_l->content = NULL;
		new_l->content_size = 0;
		return (new_l);
	}
	new_l->content = ft_memalloc(content_size);
	if (new_l->content == NULL)
	{
		free(new_l);
		return (NULL);
	}
	new_l->content = ft_memmove(new_l->content, content, content_size);
	new_l->content_size = content_size;
	return (new_l);
}
