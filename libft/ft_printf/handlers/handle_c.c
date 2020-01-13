/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 15:28:02 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:24:34 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		handle_c(va_list ap, t_str *head, t_mrk *mrk)
{
	uchar_tostr((unsigned char)va_arg(ap, int), head, mrk);
	if (!head->txt)
		return (0);
	head->is_raw = 0;
	if (mrk->minus)
		char_left_justify(' ', head);
	else
		char_right_justify(' ', head);
	return ((head->txt) ? head->len : 0);
}
