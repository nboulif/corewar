/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_print_recursion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:53:47 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:32:35 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			add_dot(t_str *head, PFPMNG mng)
{
	head->txt[head->len - mng.index - 1] = '.';
}

void			rank_tostr(t_str *head, t_mrk *mrk, PFPMNG mng,
		unsigned char rank_size)
{
	size_t		index;

	index = -1;
	while (++index < (size_t)rank_size - (size_t)mng.cur->size)
		mng.cur->value /= (ULL)mrk->base;
	index = -1;
	while (++index < mng.cur->size)
	{
		if (mng.cur->value == 0)
			head->txt[head->len - (mng.index + index) - 1] = '0';
		else
		{
			head->txt[head->len - (mng.index + index) - 1] =
				symb_lc(mng.cur->value % (ULL)mrk->base);
			mng.cur->value /= (ULL)mrk->base;
		}
	}
}

void			ornate_pfloat(t_str *head, t_mrk *mrk, PFPMNG mng, char sign)
{
	size_t		i;
	size_t		precision;

	i = mng.index;
	precision = head->len - ((sign == -1 || mrk->plus || mrk->blank) ? 1 : 0);
	while (++i < precision && mrk->zero)
		head->txt[head->len - i - 1] = '0';
	if (sign == -1)
		head->txt[head->len - 1 - i++] = '-';
	else if (mrk->plus)
		head->txt[head->len - 1 - i++] = '+';
	else if (mrk->blank)
		head->txt[head->len - 1 - i++] = ' ';
	while (i < head->len)
		head->txt[head->len - 1 - i++] = 0;
	i = head->len - mng.more_zeros - 1;
	while (++i < head->len)
		head->txt[i] = '0';
}

void			malloc_float_str(PFMNG *in, t_str *head, t_mrk *mrk,
		PFPMNG mng)
{
	ULL				value;
	size_t			index;
	unsigned char	prefix;

	value = mng.cur->value;
	index = mng.index;
	if (mng.cur->value < (ULL)mrk->base)
	{
		prefix = (in->sign == -1 || mrk->plus || mrk->blank) ? 1 : 0;
		head->len = (mrk->mfw > prefix + mng.index + 1) ?
			mrk->mfw : prefix + mng.index + 1;
		head->txt = (char*)malloc(sizeof(char) * head->len);
		if (!head->txt)
			return ;
		ornate_pfloat(head, mrk, mng, in->sign);
	}
	else
	{
		mng.cur->value /= (ULL)mrk->base;
		mng.index++;
		malloc_float_str(in, head, mrk, mng);
	}
	head->txt[head->len - index - 1] =
		symb_lc(value % (ULL)mrk->base);
}

void			main_recursion(PFMNG *in, t_str *head, t_mrk *mrk, PFPMNG mng)
{
	size_t		index;

	if ((mng.cur == in->i_e || (mng.cur->left == in->i_e &&
		in->i_e->value == 0 && in->i_e != in->i_s)) && mng.dot_index != 0)
	{
		malloc_float_str(in, head, mrk, mng);
		return ;
	}
	else
	{
		index = mng.index;
		mng.index += (mng.cur == in->i_s && !mng.dot_index) ? 1 : mng.cur->size;
		if (mng.cur == in->i_s)
			mng.dot_index = (!mng.dot_index) ? 1 : 2;
		if (mng.dot_index != 1)
			mng.cur = mng.cur->left;
		main_recursion(in, head, mrk, mng);
		mng.index = index;
		if (mng.dot_index != 1)
			mng.cur = mng.cur->right;
	}
	if (mng.dot_index == 1)
		add_dot(head, mng);
	else
		rank_tostr(head, mrk, mng, in->i_s->size);
}
