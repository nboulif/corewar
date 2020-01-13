/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:01:34 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:28:29 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			handle_u_t(va_list ap, t_str *head, t_mrk *mrk)
{
	if (mrk->len_modif)
	{
		if (*(mrk->len_modif) == 'l')
		{
			if (mrk->len_len_modif == 2)
				uint_tostr((unsigned long long)va_arg(ap, uintmax_t), head, mrk,
						0);
			else
				uint_tostr((unsigned long)va_arg(ap, uintmax_t), head, mrk, 0);
		}
		else if (*(mrk->len_modif) == 'h')
		{
			if (mrk->len_len_modif == 2)
				uint_tostr((unsigned char)va_arg(ap, uintmax_t), head, mrk, 0);
			else
				uint_tostr((unsigned short)va_arg(ap, uintmax_t), head, mrk, 0);
		}
		else if (*(mrk->len_modif) == 'j')
			uint_tostr((uintmax_t)va_arg(ap, uintmax_t), head, mrk, 0);
		else if (*(mrk->len_modif) == 'z')
			uint_tostr((size_t)va_arg(ap, size_t), head, mrk, 0);
	}
	else
		uint_tostr((unsigned int)va_arg(ap, uintmax_t), head, mrk, 0);
}

size_t			handle_u(va_list ap, t_str *head, t_mrk *mrk)
{
	mrk->base = 10;
	handle_u_t(ap, head, mrk);
	if (!head->txt && head->len != 0)
		return (0);
	if (head->len == 0)
		return (-1);
	head->is_raw = 0;
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
