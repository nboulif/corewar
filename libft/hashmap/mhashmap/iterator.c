/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:42:58 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 21:42:59 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_hmap_fill_marray(t_hmap *hmap, t_marray *marray)
{
	return (ft_hmap_bnode_iteration(marray, hmap, ft_marray_add_typecast));
}
