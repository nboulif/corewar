/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 15:19:39 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:21:58 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			uchar_tostr(unsigned char in, t_str *head, t_mrk *mrk)
{
	size_t		i;

	head->len = (mrk->mfw > 1) ? mrk->mfw : 1;
	head->txt = (char*)malloc(sizeof(char) * head->len);
	if (!head->txt)
		return ;
	head->txt[head->len - 1] = (char)in;
	i = -1;
	while (++i < head->len - 1)
		head->txt[i] = 0;
}
