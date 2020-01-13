/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_conversion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 11:21:06 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:22:46 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			float_tostr(PFMNG *in, t_str *head, t_mrk *mrk)
{
	PFPMNG			mng;

	mng.index = 0;
	mng.dot_index = 0;
	mng.cur = in->d_e;
	mng.more_zeros = 0;
	while (mng.cur->value == 0 && mng.cur != in->i_s)
		mng.cur = mng.cur->left;
	if (mng.cur == in->i_s)
		mng.dot_index = (mrk->hashtag) ? 1 : 2;
	if (!mng.dot_index)
		if (!zeros_or_round(in, mrk, &mng))
			return ;
	if (mng.cur == in->i_s)
		mng.dot_index = (mrk->hashtag) ? 1 : 2;
	if (mng.dot_index)
	{
		mng.dot_index = 0;
		mrk->precision = (!mrk->arg_precision) ? 6 : mrk->precision;
		if (!mrk->hashtag && mrk->precision == 0)
			mng.dot_index = 1;
		mng.index += mrk->precision;
		mng.more_zeros = mrk->precision;
	}
	main_recursion(in, head, mrk, mng);
}
