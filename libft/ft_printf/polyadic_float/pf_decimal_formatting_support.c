/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_decimal_formatting_support.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 11:05:45 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:31:57 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ignore_zeros(PFPMNG *mng)
{
	ULL		tmp;

	tmp = mng->cur->value;
	while (!(tmp % 10))
	{
		mng->cur->size--;
		tmp /= 10;
	}
}

unsigned char	d_rank_right(PF **cur, unsigned char d_rank,
		unsigned char rank_size)
{
	if (d_rank == 1)
	{
		*cur = (*cur)->right;
		return (rank_size);
	}
	return (d_rank - 1);
}

ULL				generate_base(unsigned char d_rank)
{
	ULL			base;

	base = 1;
	while (--d_rank > 0)
		base *= 10;
	return (base);
}

unsigned char	extract_digit(ULL value, unsigned char d_rank)
{
	return ((value / generate_base(d_rank)) % 10);
}

unsigned char	find_nonzero_digit(PF *cur, unsigned char d_rank,
		unsigned char rank_size)
{
	unsigned char	s_rank;
	unsigned char	prev_prev;

	s_rank = d_rank_right(&cur, d_rank, rank_size);
	if (cur == NULL)
		return (0);
	else if ((prev_prev = extract_digit(cur->value, s_rank)) == 0)
		return (find_nonzero_digit(cur, s_rank, rank_size));
	else
		return (prev_prev);
}
