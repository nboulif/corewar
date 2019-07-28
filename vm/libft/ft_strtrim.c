/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:51:58 by nboulif           #+#    #+#             */
/*   Updated: 2018/11/22 18:22:20 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	uint32_t	i;
	uint32_t	len_s;

	if (!s)
		return (NULL);
	i = 0;
	len_s = ft_strlen(s);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	while (s[i] && (s[len_s - 1] == ' ' || s[len_s - 1] == '\t'
		|| s[len_s - 1] == '\n'))
		len_s--;
	len_s = (int)(len_s - i) < 0 ? 0 : len_s - i;
	if (!(str = ft_strnew(len_s)))
		return (NULL);
	ft_strncpy(str, s + i, len_s);
	return (str);
}
