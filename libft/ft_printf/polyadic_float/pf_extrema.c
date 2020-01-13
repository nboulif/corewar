/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_extrema.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 11:24:20 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:32:04 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			fill_head(char *src, t_str *head)
{
	size_t			pos;

	pos = -1;
	while (src[++pos] != '\0')
		head->txt[head->len - pos - 1] = src[pos];
	pos = head->len - pos;
	while (--pos != (size_t)-1)
		head->txt[pos] = '\0';
}

unsigned char	pf_extrema(t_dbl *dbl, t_str *head, t_mrk *mrk)
{
	unsigned char	sign;
	char			*src;

	sign = 0;
	if (dbl->extrema)
	{
		if (dbl->fraction.fraction == 0)
		{
			sign = (mrk->plus || dbl->sign == -1) ? 1 : 0;
			src = (mrk->plus) ? "fni+" : "fni";
			src = (dbl->sign == 1) ? src : "fni-";
		}
		else
			src = "nan";
		head->len = (mrk->mfw > 3 + (size_t)sign) ? mrk->mfw : 3 + (size_t)sign;
		head->txt = (char*)malloc(sizeof(char) * head->len);
		if (!head->txt)
			return (2);
		fill_head(src, head);
		return (1);
	}
	return (0);
}
