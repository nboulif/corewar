/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 16:05:10 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/04 16:05:11 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_btree_replace(t_btree *btree, void *item)
{
	t_bnode			*target;
	void			*out;

	if (!btree || !item)
		return (NULL);
	target = ft_btree_get_bnode(btree, item);
	if (!target->rank)
		return (NULL);
	out = target->named;
	target->named = item;
	return (out);
}
