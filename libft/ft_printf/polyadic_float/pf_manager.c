/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 11:17:54 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:32:18 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ULL				find_most_significant_bit(ULL in)
{
	size_t			bits;

	bits = 1;
	while (bits < sizeof(in) * 8)
	{
		in |= in >> bits;
		bits = bits << 1;
	}
	return ((in >> 1) + 1);
}

unsigned char	add_shadow(PFMNG *mng, PFMNG *shadow)
{
	t_polyadic_float	*shadow_cur;
	t_polyadic_float	*cur;
	int					offset;

	cur = mng->d_e;
	shadow_cur = shadow->d_e;
	offset = cur->index - shadow_cur->index;
	while (offset-- > 0)
		if (!(cur = add_right(0, mng)))
			return (0);
	while (shadow_cur && cur)
	{
		cur->value += shadow_cur->value;
		if (!add_inc(cur, mng))
			return (0);
		cur = cur->left;
		shadow_cur = shadow_cur->left;
	}
	return (1);
}

unsigned char	decode_fraction(t_dbl *dbl, PFMNG *mng, PFMNG *shadow)
{
	unsigned int	left_offset;
	ULL				active_bit;

	shadow->d_s->value = PFBASE >> 1;
	left_offset = 0;
	while (left_offset++ < dbl->fraction.left_offset)
		shift_right(shadow);
	active_bit = find_most_significant_bit(dbl->fraction.fraction);
	while (dbl->fraction.fraction > 0 && active_bit)
	{
		if (dbl->fraction.fraction & active_bit)
		{
			add_shadow(mng, shadow);
			dbl->fraction.fraction -= active_bit;
		}
		active_bit = active_bit >> 1;
		shift_right(shadow);
	}
	return (1);
}

PFMNG			*pf_manager(t_dbl *dbl)
{
	PFMNG			*mng;
	PFMNG			*shadow;

	mng = init_pfmng(dbl);
	if (!mng || !(shadow = init_pfmng(dbl)))
	{
		free(mng);
		free(dbl);
		return (NULL);
	}
	mng->i_s->value = dbl->normalized;
	decode_fraction(dbl, mng, shadow);
	if (dbl->exponent > 0)
		while ((dbl->exponent)-- > 0)
			shift_left(mng);
	else
		while ((dbl->exponent)++ < 0)
			shift_right(mng);
	free(dbl);
	clean_pfmng(shadow);
	return (mng);
}
