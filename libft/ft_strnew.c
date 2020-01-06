/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 12:06:36 by nsondag           #+#    #+#             */
/*   Updated: 2018/06/23 12:06:58 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *b;

	if (!(b = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(b, size + 1);
	return (b);
}
