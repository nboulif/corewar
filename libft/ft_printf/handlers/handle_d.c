/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 16:58:26 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:24:43 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			handle_d_t(va_list ap, t_str *head, t_mrk *mrk)
{
	if (mrk->len_modif)
	{
		if (*(mrk->len_modif) == 'l')
		{
			if (mrk->len_len_modif == 2)
				int_tostr((long long)va_arg(ap, intmax_t), head, mrk, 0);
			else
				int_tostr((long)va_arg(ap, intmax_t), head, mrk, 0);
		}
		else if (*(mrk->len_modif) == 'h')
		{
			if (mrk->len_len_modif == 2)
				int_tostr((char)va_arg(ap, intmax_t), head, mrk, 0);
			else
				int_tostr((short)va_arg(ap, intmax_t), head, mrk, 0);
		}
		else if (*(mrk->len_modif) == 'j')
			int_tostr((intmax_t)va_arg(ap, intmax_t), head, mrk, 0);
		else if (*(mrk->len_modif) == 'z')
			int_tostr((ssize_t)va_arg(ap, intmax_t), head, mrk, 0);
	}
	else
		int_tostr((int)va_arg(ap, intmax_t), head, mrk, 0);
}

size_t			handle_d(va_list ap, t_str *head, t_mrk *mrk)
{
	mrk->base = 10;
	handle_d_t(ap, head, mrk);
	if (!head->txt && head->len != 0)
		return (0);
	if (head->len == 0)
		return (-1);
	head->is_raw = 0;
	if (mrk->minus)
		left_justify(' ', head, mrk);
	else
		right_justify(' ', head, mrk);
	return ((head->txt) ? head->len : 0);
}
