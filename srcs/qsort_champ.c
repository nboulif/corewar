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

int		cmp_champ_order(t_process *champ1, t_process *champ2)
{
	if (champ1->origin_champ->index > champ2->origin_champ->index)
		return (-1);
	else if (champ1->origin_champ->index == champ2->origin_champ->index)
		return (0);
	return (1);
}

void	swap_proc(t_process *stack_proc, int a, int b)
{
	t_process	tmp;

	tmp = stack_proc[a];
	stack_proc[a] = stack_proc[b];
	stack_proc[b] = tmp;
}

int		partition(t_process *stack_proc, int start_ind, int size)
{
	t_process	*value_piv;
	int			piv_i;
	int			i;

	i = start_ind - 1;
	value_piv = &stack_proc[size - 1];
	piv_i = start_ind;
	while (++i < size)
		if (cmp_champ_order(value_piv, &stack_proc[i]) == -1)
			swap_proc(stack_proc, i, piv_i++);
	swap_proc(stack_proc, size - 1, piv_i);
	return (piv_i);
}

void	qsort_proc(t_process *stack_proc, int start_ind, int size)
{
	int pivot_i;

	if (start_ind >= size)
		return ;
	pivot_i = partition(stack_proc, start_ind, size);
	qsort_proc(stack_proc, start_ind, pivot_i);
	qsort_proc(stack_proc, pivot_i + 1, size);
}
