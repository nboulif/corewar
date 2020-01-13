/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_decimal_formatting.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 11:03:50 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:31:51 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	round_up(PFMNG *in, PFPMNG *mng, unsigned char d_rank)
{
	t_polyadic_float	*cur;

	mng->cur->inc = generate_base(d_rank);
	cur = mng->cur;
	while (cur)
	{
		if (!add_inc(cur, in))
			return (0);
		cur = cur->left;
	}
	return (1);
}

unsigned char	round_pfloat(PFMNG *in, PFPMNG *mng, int keep)
{
	unsigned char		last_digit;
	unsigned char		prev_digit;
	unsigned char		d_rank;
	t_polyadic_float	*cur;

	while (keep <= 0)
	{
		keep += (int)mng->cur->size;
		mng->cur = mng->cur->left;
	}
	mng->cur = mng->cur->right;
	mng->cur->size = keep;
	d_rank = in->i_s->size - keep + 1;
	cur = mng->cur;
	last_digit = extract_digit(cur->value, d_rank);
	d_rank = d_rank_right(&cur, d_rank, in->i_s->size);
	prev_digit = extract_digit(cur->value, d_rank);
	if (prev_digit > 5 || (prev_digit == 5 && (last_digit % 2 != 0 ||
		find_nonzero_digit(cur, d_rank, in->i_s->size) != 0)))
		return (round_up(in, mng, in->i_s->size - keep + 1));
	return (1);
}

unsigned char	zeros_or_round(PFMNG *in, t_mrk *mrk, PFPMNG *mng)
{
	int					keep;
	int					rejected;
	t_polyadic_float	*cur;

	ignore_zeros(mng);
	rejected = mng->cur->size;
	cur = mng->cur;
	while ((cur = cur->left) != in->i_s)
		rejected += in->i_s->size;
	mrk->precision = (!mrk->arg_precision) ? 6 : mrk->precision;
	keep = (int)(mrk->precision) - rejected;
	rejected = in->i_s->size - mng->cur->size;
	if (keep >= rejected)
	{
		mng->more_zeros = keep - rejected;
		mng->index = mng->more_zeros;
		mng->cur->size += rejected;
	}
	else if (keep >= 0)
		mng->cur->size += keep;
	else
		return (round_pfloat(in, mng, keep));
	return (1);
}
