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

int					ft_array_iteration(void *receiver, t_array *source,
	int (*f)(void *receiver, void *sent))
{
	size_t			i;
	int				out;

	i = 0;
	out = 1;
	while (out && i < source->n_items)
	{
		out = f(receiver, ft_array_get(source, i));
		++i;
	}
	return (out);
}

int					ft_array_add_typecast(void *receiver, void *sent)
{
	return (ft_array_add((t_array*)receiver, sent));
}

int					ft_array_fill_copy(t_array *old, t_array *new_array)
{
	return (ft_array_iteration(new_array, old, ft_array_add_typecast));
}
