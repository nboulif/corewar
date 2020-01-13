/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 14:14:56 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/20 18:50:39 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*first;
	t_list		*track;

	if (lst == NULL || f == NULL)
		return (NULL);
	first = f(lst);
	if (first == NULL)
		return (NULL);
	track = first;
	while ((lst = lst->next) != NULL)
	{
		track->next = f(lst);
		track = track->next;
		if (track == NULL)
		{
			ft_lstdel(&first, ft_lstdel_content);
			return (NULL);
		}
	}
	return (first);
}
