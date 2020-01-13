/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_xmaj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:05:28 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:29:22 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			handle_x_maj(va_list ap, t_str *head, t_mrk *mrk)
{
	mrk->base = 16;
	if (mrk->hashtag)
		mrk->len_prefix = 2;
	handle_u_t(ap, head, mrk);
	if (!head->txt && head->len != 0)
		return (0);
	if (head->len == 0)
		return (-1);
	head->is_raw = 0;
	if (mrk->len_prefix && (!mrk->zero || mrk->minus || mrk->arg_precision))
		add_prefix("X0", head);
	if (mrk->minus)
		left_justify(' ', head, mrk);
	else
	{
		if (mrk->zero && !mrk->arg_precision)
		{
			right_justify('0', head, mrk);
			if (mrk->len_prefix)
				force_prefix("0X", head);
		}
		else
			right_justify(' ', head, mrk);
	}
	return ((head->txt) ? head->len : 0);
}
