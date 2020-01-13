/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pctg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 17:08:46 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:25:25 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			handle_pctg(t_str *head, t_mrk *mrk)
{
	uchar_tostr('%', head, mrk);
	if (!head->txt)
		return (0);
	head->is_raw = 0;
	if (mrk->minus)
		left_justify(' ', head, mrk);
	else
		right_justify(' ', head, mrk);
	return ((head->txt) ? head->len : 0);
}
