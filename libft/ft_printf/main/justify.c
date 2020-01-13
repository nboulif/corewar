/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   justify.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 10:38:12 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:31:27 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			left_justify(char filler, t_str *head, t_mrk *mrk)
{
	size_t		offset;
	size_t		pos;

	offset = -1;
	while (++offset < mrk->mfw && !head->txt[offset])
		;
	if (offset > 0)
	{
		pos = offset - 1;
		while (++pos < head->len)
			head->txt[pos - offset] = head->txt[pos];
	}
	pos = head->len - offset - 1;
	while (++pos < head->len)
		head->txt[pos] = filler;
}

void			right_justify(char filler, t_str *head, t_mrk *mrk)
{
	size_t		offset;

	offset = -1;
	while (++offset < mrk->mfw && !head->txt[offset])
		head->txt[offset] = filler;
}

void			char_right_justify(char filler, t_str *head)
{
	size_t		offset;

	offset = -1;
	while (++offset < head->len - 1)
		head->txt[offset] = filler;
}

void			char_left_justify(char filler, t_str *head)
{
	size_t		offset;
	size_t		pos;

	offset = -1;
	while (++offset < head->len - 1)
		;
	if (offset > 0)
	{
		pos = offset - 1;
		while (++pos < head->len)
			head->txt[pos - offset] = head->txt[pos];
	}
	pos = head->len - offset - 1;
	while (++pos < head->len)
		head->txt[pos] = filler;
}
