/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:02:04 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:25:15 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			handle_p(va_list ap, t_str *head, t_mrk *mrk)
{
	mrk->base = 16;
	mrk->hashtag = 1;
	mrk->len_prefix = 2;
	uint_tostr((uintmax_t)va_arg(ap, void*), head, mrk, 0);
	if (!head->txt && head->len != 0)
		return (0);
	if (head->len == 0)
		return (-1);
	head->is_raw = 0;
	add_prefix("x0", head);
	if (mrk->minus)
		left_justify(' ', head, mrk);
	else
		right_justify(' ', head, mrk);
	return ((head->txt) ? head->len : 0);
}
