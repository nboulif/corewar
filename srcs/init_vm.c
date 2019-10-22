#include "vm_corewar.h"

int			cmp_champ_order(t_process *champ1, t_process *champ2)
{
	if (champ1->origin_champ->index > champ2->origin_champ->index)
		return (1);
	else if (champ1->origin_champ->index == champ2->origin_champ->index)
		return (0);
	return (-1);
}

void	swap_champ(t_array *stack_champ, int a, int b)
{
	t_process	tmp;

	tmp = *(t_process*)ft_array_get(stack_champ, a);
	*(t_process*)ft_array_get(stack_champ, a) = *(t_process*)ft_array_get(stack_champ, b);
	*(t_process*)ft_array_get(stack_champ, b) = tmp;
}

int		partition(t_array *stack_champ, int start_ind, int size)
{
	t_process *value_piv;
	int	piv_i;

	value_piv = ft_array_get(stack_champ, size - 1);
	piv_i = start_ind;
	for (int i = start_ind; i < size; i++)
		if (cmp_champ_order(value_piv, ft_array_get(stack_champ, i)) == 1)
			swap_champ(stack_champ, i, piv_i++);
	swap_champ(stack_champ, size - 1, piv_i);
	return (piv_i);
}

void	qsort_champ(t_array *stack_champ, int start_ind, int size)
{
	int pivot_i;

	pivot_i = partition(stack_champ , start_ind, size);
	if (start_ind < pivot_i)
		qsort_champ(stack_champ, start_ind, pivot_i);
	if (pivot_i + 1 < size)
		qsort_champ(stack_champ, pivot_i + 1, size);
}

void		init_vm(t_all *all)
{
	int			i;
	t_process	*proc;

	i = 0;
	if (!(all->stack_champ = ft_array_construct(all->nb_champ, sizeof(t_process))))
		print_error_and_exit(MALLOC_ERROR);
	while (i < all->nb_champ)
	{
		proc = ft_array_inject(all->stack_champ);
		ft_bzero(proc, sizeof(t_process));
		proc->origin_champ = &all->champ[i++];
	}
    qsort_champ(all->stack_champ, 0, all->stack_champ->n_items);
}