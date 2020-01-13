/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:16:51 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/20 18:02:45 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd(t_list **alst, t_list *elem)
{
	if (elem == NULL || alst == NULL)
		return ;
	if (*alst == NULL)
	{
		*alst = elem;
		elem->next = NULL;
		return ;
	}
	elem->next = *alst;
	*alst = elem;
}
