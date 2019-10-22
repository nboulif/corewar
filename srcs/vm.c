#include "vm_corewar.h"

void		next_action(t_all *all, t_process *current_process)
{
	if (current_process->wait)
	{
		current_process->wait--;
		return ;
	}
}

void		vm(t_all *all)
{
	int cycle;
	int i;

	cycle = 0;
	init_vm(all);
	while (cycle)
	{
		i = 0;
		while (i < all->stack_champ->n_items)
			next_action(all, (t_process*)ft_array_get(all->stack_champ, i++));
		cycle++;
	}
}
