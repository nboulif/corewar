#include "vm_corewar.h"

int			cmp_champ_order(t_process *champ1, t_process *champ2)
{
	if (champ1->origin_champ->index < champ2->origin_champ->index)
		return (-1);
	else if (champ1->origin_champ->index == champ2->origin_champ->index)
		return (0);
	return (1);
}

void	swap_proc(t_array *stack_proc, int a, int b)
{
	t_process	tmp;

	tmp = *(t_process*)ft_array_get(stack_proc, a);
	*(t_process*)ft_array_get(stack_proc, a) = *(t_process*)ft_array_get(stack_proc, b);
	*(t_process*)ft_array_get(stack_proc, b) = tmp;
}

int		partition(t_array *stack_proc, int start_ind, int size)
{
	t_process *value_piv;
	int	piv_i;

	value_piv = ft_array_get(stack_proc, size - 1);
	piv_i = start_ind;
	for (int i = start_ind; i < size; i++)
		if (cmp_champ_order(value_piv, ft_array_get(stack_proc, i)) == -1)
			swap_proc(stack_proc, i, piv_i++);
	swap_proc(stack_proc, size - 1, piv_i);
	return (piv_i);
}

void	qsort_proc(t_array *stack_proc, int start_ind, int size)
{
	int pivot_i;

	if (start_ind >= size)
		return ;
	pivot_i = partition(stack_proc , start_ind, size);
	qsort_proc(stack_proc, start_ind, pivot_i);
	qsort_proc(stack_proc, pivot_i + 1, size);
}

void		init_map(t_all *all)
{
	int i;

	i = -1;
	if (!(all->map.character = malloc(sizeof(char) * MEM_SIZE)) ||
		!(all->map.color_in_map = malloc(sizeof(char*) * MEM_SIZE)))
		print_error_and_exit(MALLOC_ERROR);
	ft_bzero(all->map.character, sizeof(char) * MEM_SIZE);
	while (++i < MEM_SIZE)
		all->map.color_in_map[i] = text_color[9];
}

void		init_color_in_map(t_all *all)
{
	int			i;
	int			x;
	int			start_code;
	t_process	*proc;

	i = -1;
	while (++i < all->nb_champ)
	{
		x = -1;
		proc = ft_array_get(all->stack_proc, i);
		while (++x < proc->origin_champ->size_exec)
			all->map.color_in_map[x + proc->pc] = text_color[proc->origin_champ->index_player];
	}
}

void		init_vm(t_all *all)
{
	int			i;
	t_process	*proc;
	int			min_ind;
	int			i_undif;

	i_undif = 0;
	min_ind = 127;
	i = -1;
	init_map(all);
	if (!(all->stack_proc = ft_array_construct(all->nb_champ, sizeof(t_process))))
		print_error_and_exit(MALLOC_ERROR);
	ft_bzero(all->map.character, MEM_SIZE);
	while (++i < all->nb_champ)
	{
		ft_memcpy(all->map.character + i * (MEM_SIZE / all->nb_champ), all->champ[i].exec_code, all->champ[i].size_exec);
		ft_bzero((proc = ft_array_inject(all->stack_proc)), sizeof(t_process));
		ft_bzero(proc->reg, sizeof(int) * REG_NUMBER);
		proc->origin_champ = &all->champ[i];
		proc->pc = i * (MEM_SIZE / all->nb_champ);
		proc->carry = 0;
		if (all->champ[i].flag_index && min_ind > all->champ[i].index)
			min_ind = all->champ[i].index;
	}
	(min_ind == 127) ? (min_ind = 0): 1;
	i = -1;
	while (++i < all->nb_champ)
	{
		if (!all->champ[i].flag_index)
			all->champ[i].index = min_ind - ++i_undif;
		((t_process*)ft_array_get(all->stack_proc, i))->reg[0] = all->champ[i].index;
	}
	qsort_proc(all->stack_proc, 0, all->nb_champ);
	i = -1;
	t_process *cur;
	while (++i < all->nb_champ)
	{
		cur = (t_process*)ft_array_get(all->stack_proc, i);
		cur->origin_champ->index_player = i + 1;
		cur->index = i + 1;
	}
	init_color_in_map(all);
}