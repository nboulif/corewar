/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:49:32 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/10 13:49:33 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_btree_cmp_ascii(void *s1, void *s2)
{
	return (ft_strcmp(*(char**)s1, *(char**)s2));
}

int					ft_btree_cmp_size(void *s1, void *s2)
{
	if (*(size_t*)s1 < *(size_t*)s2)
		return (-1);
	else if (*(size_t*)s1 == *(size_t*)s2)
		return (0);
	else
		return (1);
}

int					ft_btree_cmp_addr(void *s1, void *s2)
{
	if ((uintmax_t)s1 < (uintmax_t)s2)
		return (-1);
	else if ((uintmax_t)s1 == (uintmax_t)s2)
		return (0);
	else
		return (1);
}
