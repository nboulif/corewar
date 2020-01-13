/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 19:58:25 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:30:01 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_str			*init_str(t_str *s)
{
	s = (t_str*)malloc(sizeof(t_str));
	if (!s)
		return (NULL);
	s->txt = NULL;
	s->len = 0;
	s->next = NULL;
	s->is_raw = 1;
	return (s);
}

t_str			*clean_str(t_str *s)
{
	if (s)
	{
		if (!s->is_raw)
			free(s->txt);
		clean_str(s->next);
		free(s);
	}
	return (NULL);
}

void			init_mrk(t_mrk *m)
{
	m->zero = 0;
	m->minus = 0;
	m->plus = 0;
	m->hashtag = 0;
	m->blank = 0;
	m->len_prefix = 0;
	m->mfw = 0;
	m->arg_precision = 0;
	m->precision = 0;
	m->len_modif = NULL;
	m->len_len_modif = 0;
	m->type = 0;
	m->base = 0;
}
