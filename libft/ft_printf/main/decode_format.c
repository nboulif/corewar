/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 20:41:54 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:30:34 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*copy_raw_ignore(char *cur, t_str *head, size_t start,
		size_t *len)
{
	while (cur[++start] && cur[start] != '%')
		;
	head->txt = cur;
	head->len = start;
	*len += start;
	return (cur + start);
}

char			*copy_raw(char *cur, t_str *head, size_t *len)
{
	return (copy_raw_ignore(cur, head, -1, len));
}

char			*decode_identifier(va_list ap, char *cur, t_str *head,
		size_t *len)
{
	t_mrk		mrk;
	char		*base_cur;

	base_cur = cur;
	init_mrk(&mrk);
	cur = inspect_flags(cur + 1, &mrk);
	cur = inspect_mfw(cur, &mrk);
	cur = inspect_precision(cur, &mrk);
	cur = inspect_length_modifier(cur, &mrk);
	cur = (inspect_arg_type(ap, cur, head, &mrk)) ? cur + 1 : NULL;
	*len += head->len;
	if (!cur)
		return (copy_raw_ignore(base_cur, head, 0, len));
	else
		return (cur);
}

t_str			*decode_format(va_list ap, const char *format, size_t *len)
{
	char		*cur;
	t_str		*root;
	t_str		*head;
	t_str		*prev;

	root = NULL;
	if (!(root = init_str(root)))
		return (NULL);
	head = root;
	prev = NULL;
	cur = (char*)format;
	while (1)
	{
		if (*cur == '%')
			cur = decode_identifier(ap, cur, head, len);
		else
			cur = copy_raw(cur, head, len);
		if (!(*cur))
			return (root);
		prev = head;
		if (!(head = init_str(head)))
			return (clean_str(root));
		prev->next = head;
	}
}
