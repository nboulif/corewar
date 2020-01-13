/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 16:20:12 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/20 17:40:37 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strcmp(const char *s1, const char *s2)
{
	size_t		i;

	i = 0;
	while (s1[i] != '\0' && (unsigned char)s1[i] - (unsigned char)s2[i] == 0)
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
