/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsigned_conversion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 15:19:17 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:23:11 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	addon_prefix(uintmax_t in, t_mrk *mrk, size_t index)
{
	if (mrk->arg_precision && mrk->hashtag &&
		!(index == 0 && in == 0) && (mrk->type == 'x' ||
			mrk->type == 'X'))
	{
		if (mrk->precision >= mrk->mfw)
			return (2);
		else if (mrk->mfw == mrk->precision + 1)
			return (1);
	}
	return (0);
}

static void		re_uint_tostr(uintmax_t in, t_str *head, t_mrk *mrk,
			size_t index)
{
	size_t		i;

	if (in < mrk->base)
	{
		if (in == 0 && index == 0 && mrk->type != 'p')
			mrk->len_prefix = 0;
		i = (mrk->mfw > mrk->precision) ? mrk->mfw : mrk->precision;
		i += addon_prefix(in, mrk, index);
		head->len = (i > index + 1 + mrk->len_prefix) ? i : index + 1 +
			mrk->len_prefix;
		head->txt = (char*)malloc(sizeof(char) * head->len);
		if (!head->txt)
			return ;
		i = index;
		while (++i < mrk->precision)
			head->txt[head->len - 1 - i] = '0';
		while (i < head->len)
			head->txt[head->len - 1 - i++] = 0;
	}
	else
		re_uint_tostr(in / mrk->base, head, mrk, index + 1);
	head->txt[head->len - index - 1] = (mrk->type == 'X') ?
		symb_uc(in % mrk->base) : symb_lc(in % mrk->base);
}

void			uint_tostr(uintmax_t in, t_str *head, t_mrk *mrk, size_t index)
{
	size_t			i;

	if (!(in == 0 && index == 0 &&
				mrk->arg_precision && mrk->precision == 0))
		return (re_uint_tostr(in, head, mrk, index));
	if (mrk->mfw == 0 && !(mrk->type == 'o' && mrk->hashtag))
		return ;
	i = (mrk->mfw > mrk->precision) ? mrk->mfw : mrk->precision;
	head->len = (i > mrk->len_prefix) ? i : mrk->len_prefix;
	head->txt = (char*)malloc(sizeof(char) * head->len);
	if (!head->txt)
		return ;
	i = index - 1;
	while (++i < mrk->precision)
		head->txt[head->len - 1 - i] = '0';
	while (i < head->len)
		head->txt[head->len - 1 - i++] = 0;
}
