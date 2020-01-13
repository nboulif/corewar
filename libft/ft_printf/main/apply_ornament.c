/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_ornament.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 21:02:41 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:29:39 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			add_prefix(char *prefix, t_str *head)
{
	size_t		offset;
	size_t		pos;

	offset = -1;
	while (++offset < head->len && !head->txt[offset])
		;
	pos = -1;
	--offset;
	while (prefix[++pos] && offset >= pos)
		head->txt[offset - pos] = prefix[pos];
}

void			force_prefix(char *prefix, t_str *head)
{
	size_t		pos;

	pos = -1;
	while (prefix[++pos])
		head->txt[pos] = prefix[pos];
}

void			appleft_prefix(char *prefix, t_str *head, size_t len_prefix,
		char ignore)
{
	size_t		offset;
	size_t		pos;

	offset = -1;
	while (head->txt[++offset] != ignore)
		;
	pos = offset - 1;
	while (++pos < offset + len_prefix)
		head->txt[pos] = head->txt[pos - len_prefix];
	force_prefix(prefix, head);
}

char			next_digit(t_str *head)
{
	size_t		pos;

	pos = -1;
	while (++pos < head->len)
	{
		if (head->txt[pos] != '\0')
			return (head->txt[pos]);
	}
	return ('\0');
}
