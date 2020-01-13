/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_o.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:03:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:28:00 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			handle_o(va_list ap, t_str *head, t_mrk *mrk)
{
	mrk->base = 8;
	if (mrk->hashtag)
		mrk->len_prefix = 1;
	handle_u_t(ap, head, mrk);
	if (!head->txt && head->len != 0)
		return (0);
	if (head->len == 0)
		return (-1);
	head->is_raw = 0;
	if (mrk->len_prefix && (((!mrk->zero || mrk->arg_precision)) ||
				(mrk->zero && !mrk->arg_precision)))
	{
		if (next_digit(head) != '0')
			add_prefix("0", head);
	}
	if (mrk->minus)
		left_justify(' ', head, mrk);
	else
	{
		if (mrk->zero && !mrk->arg_precision)
			right_justify('0', head, mrk);
		else
			right_justify(' ', head, mrk);
	}
	return ((head->txt) ? head->len : 0);
}
