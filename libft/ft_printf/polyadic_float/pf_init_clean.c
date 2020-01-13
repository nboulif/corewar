/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_init_clean.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:51:44 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:32:11 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

PFMNG			*init_pfmng(t_dbl *dbl)
{
	PFMNG		*mng;

	mng = (PFMNG*)malloc(sizeof(PFMNG));
	if (!mng)
		return (NULL);
	mng->sign = dbl->sign;
	if (!(mng->i_s = init_pf(0, NULL, NULL)))
	{
		free(mng);
		return (NULL);
	}
	mng->i_e = mng->i_s;
	if (!(mng->d_s = init_pf(0, mng->i_s, NULL)))
	{
		free(mng->i_s);
		free(mng);
		return (NULL);
	}
	mng->d_e = mng->d_s;
	return (mng);
}

PF				*init_pf(ULL value, PF *left, PF *right)
{
	PF			*pf;

	pf = (PF*)malloc(sizeof(PF));
	if (!pf)
		return (NULL);
	pf->value = value;
	pf->right = right;
	pf->index = 0;
	pf->inc = PFBASE;
	pf->size = 0;
	while ((pf->inc /= 10) > 0)
		pf->size++;
	if (right)
	{
		pf->index = right->index + 1;
		right->left = pf;
	}
	pf->left = left;
	if (left)
	{
		pf->index = left->index - 1;
		left->right = pf;
	}
	return (pf);
}

void			clean_pfmng(PFMNG *mng)
{
	PF			*cur;
	PF			*prev;

	prev = mng->d_e;
	if (!prev)
		return ;
	cur = prev->left;
	while (prev)
	{
		free(prev);
		prev = cur;
		if (prev)
			cur = prev->left;
	}
	free(mng);
}
