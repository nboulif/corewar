/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_x.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:04:37 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:29:16 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			handle_x(va_list ap, t_str *head, t_mrk *mrk)
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
		add_prefix("x0", head);
	if (mrk->minus)
		left_justify(' ', head, mrk);
	else
	{
		if (mrk->zero && (!mrk->arg_precision))
		{
			right_justify('0', head, mrk);
			if (mrk->len_prefix)
				force_prefix("0x", head);
		}
		else
			right_justify(' ', head, mrk);
	}
	return ((head->txt) ? head->len : 0);
}
