/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 20:26:13 by nsondag           #+#    #+#             */
/*   Updated: 2018/06/24 17:46:58 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*dst;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	len = ft_strlen(s);
	while ((s[len - 1] == ' ' || s[len - 1] == '\n' \
				|| s[len - 1] == '\t') && len != i)
		len--;
	if (!(dst = ft_strnew(len - i)))
		return (NULL);
	dst = ft_strsub(s, i, len - i);
	dst[len - i + 1] = '\0';
	return (dst);
}
