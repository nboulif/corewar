/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 14:40:43 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/20 18:17:55 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_strdel_ptr(char ***arr)
{
	size_t		i;

	if (arr == NULL || *arr == NULL || **arr == NULL)
		return ;
	i = -1;
	while ((*arr)[++i] != NULL)
		free((*arr)[i]);
	free(*arr);
	*arr = NULL;
}
