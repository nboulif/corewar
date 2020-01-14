/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 17:04:39 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/20 17:04:41 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

int		cmp_champ_order(t_champ *champ1, t_champ *champ2)
{
	if (champ1->index > champ2->index)
		return (-1);
	else if (champ1->index == champ2->index)
		return (0);
	return (1);
}

void	swap_champ(t_champ *champ, int a, int b)
{
	t_champ		tmp;

	tmp = champ[a];
	champ[a] = champ[b];
	champ[b] = tmp;
}

int		partition(t_champ *champ, int start_ind, int size)
{
	t_champ		*value_piv;
	int			piv_i;
	int			i;

	i = start_ind - 1;
	value_piv = &champ[size - 1];
	piv_i = start_ind;
	while (++i < size)
		if (cmp_champ_order(value_piv, &champ[i]) == -1)
			swap_champ(champ, i, piv_i++);
	swap_champ(champ, size - 1, piv_i);
	return (piv_i);
}

void	qsort_champ(t_champ *champ, int start_ind, int size)
{
	int			pivot_i;

	if (start_ind >= size)
		return ;
	pivot_i = partition(champ, start_ind, size);
	qsort_champ(champ, start_ind, pivot_i);
	qsort_champ(champ, pivot_i + 1, size);
}
