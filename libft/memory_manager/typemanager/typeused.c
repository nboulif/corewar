/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   typeused.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 19:26:40 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/29 19:26:41 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_typeused_initialize(t_typeused *typeused)
{
	typeused->typeitem = NULL;
	typeused->oldest = NULL;
	typeused->recovery = NULL;
	typeused->last = NULL;
}

void				ft_typeused_recover(t_typeused *typeused,
	t_typeitem *typeitem)
{
	typeitem->next_recovery = typeused->recovery;
	typeused->recovery = typeitem;
}
