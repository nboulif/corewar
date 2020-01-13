/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 12:27:18 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/08 14:33:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strequ(char const *s1, char const *s2)
{
	if (s1 == NULL)
	{
		if (s2 == NULL)
			return (1);
		return (0);
	}
	else if (s2 == NULL)
		return (0);
	return (ft_strcmp(s1, s2) == 0);
}
