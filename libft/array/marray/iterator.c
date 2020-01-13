/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 14:51:16 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 14:51:17 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_marray_add_typecast(void *receiver, void *sent)
{
	return (ft_marray_add((t_marray*)receiver, sent));
}

int					ft_array_fill_mcopy(t_array *old, t_marray *new_marray)
{
	return (ft_array_iteration(new_marray, old, ft_marray_add_typecast));
}
