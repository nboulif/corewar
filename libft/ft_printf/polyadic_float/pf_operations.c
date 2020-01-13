/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_operations.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:44:48 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:32:27 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

PF				*add_right(ULL value, PFMNG *mng)
{
	if (!init_pf(value, mng->d_e, NULL))
		return (NULL);
	mng->d_e = mng->d_e->right;
	return (mng->d_e);
}

PF				*add_left(ULL value, PFMNG *mng)
{
	if (!init_pf(value, NULL, mng->i_e))
		return (NULL);
	mng->i_e = mng->i_e->left;
	return (mng->i_e);
}

unsigned char	add_inc(PF *pf, PFMNG *mng)
{
	pf->value += pf->inc;
	while (pf->value >= PFBASE)
	{
		pf->value -= PFBASE;
		if (!pf->left && !add_left(0, mng))
			return (0);
		pf->left->inc += 1;
	}
	pf->inc = 0;
	return (1);
}

unsigned char	shift_right(PFMNG *mng)
{
	PF				*cur;

	if ((mng->d_e->value & 1) && !add_right(0, mng))
		return (0);
	cur = mng->d_e;
	while (cur)
	{
		if (cur->value & 1)
			cur->right->inc = PFBASE >> 1;
		cur->value = cur->value >> 1;
		cur = cur->left;
	}
	cur = mng->d_e;
	while (cur)
	{
		if (!add_inc(cur, mng))
			return (0);
		cur = cur->left;
	}
	return (1);
}

unsigned char	shift_left(PFMNG *mng)
{
	PF				*cur;

	if ((mng->i_e->value & 1) && !add_left(0, mng))
		return (0);
	cur = mng->i_e;
	while (cur)
	{
		cur->value = cur->value << 1;
		while (cur->value >= PFBASE)
		{
			cur->value -= PFBASE;
			cur->left->inc += 1;
		}
		cur = cur->right;
	}
	cur = mng->d_e->left;
	while (cur)
	{
		if (!add_inc(cur, mng))
			return (0);
		cur = cur->left;
	}
	return (1);
}
