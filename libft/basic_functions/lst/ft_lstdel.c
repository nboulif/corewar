/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 13:10:03 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/17 09:44:58 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*next;

	if (alst == NULL || *alst == NULL || del == NULL)
		return ;
	next = (*alst)->next;
	ft_lstdelone(alst, del);
	if (next != NULL)
		ft_lstdel(&next, del);
}
