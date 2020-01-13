/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 15:31:23 by dabeloos          #+#    #+#             */
/*   Updated: 2018/10/11 16:50:26 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	size_t		prefix;
	size_t		l;

	if (s == NULL)
		return (NULL);
	prefix = 0;
	while (s[prefix] == ' ' || s[prefix] == '\n' || s[prefix] == '\t')
		++prefix;
	l = ft_strlen(s + prefix) + prefix;
	while (l > prefix && (s[--l] == ' ' || s[l] == '\n' || s[l] == '\t'))
		;
	l = (l == prefix) ? 0 : l - prefix + 1;
	return (ft_strsub2(s, prefix, l));
}
