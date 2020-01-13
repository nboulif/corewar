/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signed_conversion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 15:52:22 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:22:56 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ornate_signed(t_str *head, t_mrk *mrk, size_t i, char sign)
{
	size_t		end;

	while (++i < mrk->precision ||
			((!mrk->arg_precision || mrk->mfw <= mrk->precision) &&
			!mrk->minus && mrk->zero && i < head->len))
		head->txt[head->len - 1 - i] = '0';
	end = (i == head->len) ? 1 : 0;
	if (sign == -1)
		head->txt[head->len - 1 + end - i++] = '-';
	else if (mrk->plus)
		head->txt[head->len - 1 + end - i++] = '+';
	else if (mrk->blank)
		head->txt[head->len - 1 + end - i++] = ' ';
	while (i < head->len)
		head->txt[head->len - 1 - i++] = 0;
}

static void		re_int_tostr(intmax_t in, t_str *head, t_mrk *mrk, size_t index)
{
	char			sign;
	size_t			i;
	unsigned char	prefix;

	sign = (in < 0) ? -1 : 1;
	if (in > -1 * (intmax_t)mrk->base && in < (intmax_t)mrk->base)
	{
		prefix = (sign == -1 || mrk->plus || mrk->blank) ? 1 : 0;
		i = (mrk->mfw > mrk->precision + prefix) ? mrk->mfw : mrk->precision +
			prefix;
		head->len = (i > index + 1 + prefix) ? i : index + 1 + prefix;
		head->txt = (char*)malloc(sizeof(char) * head->len);
		if (!head->txt)
			return ;
		ornate_signed(head, mrk, index, sign);
	}
	else
		re_int_tostr(in / (intmax_t)mrk->base, head, mrk, index + 1);
	head->txt[head->len - index - 1] = symb_lc(sign *
			(in % (intmax_t)mrk->base));
}

void			int_tostr(intmax_t in, t_str *head, t_mrk *mrk, size_t index)
{
	size_t			i;
	unsigned char	prefix;

	if (!(in == 0 && index == 0 &&
				mrk->arg_precision && mrk->precision == 0))
		return (re_int_tostr(in, head, mrk, index));
	if (mrk->mfw == 0)
		return ;
	i = (mrk->mfw > mrk->precision) ? mrk->mfw : mrk->precision;
	prefix = (mrk->plus || mrk->blank) ? 1 : 0;
	head->len = (i > 1 + (size_t)prefix) ? i : 1 + (size_t)prefix;
	head->txt = (char*)malloc(sizeof(char) * head->len);
	if (!head->txt)
		return ;
	ornate_signed(head, mrk, -1, 1);
}
