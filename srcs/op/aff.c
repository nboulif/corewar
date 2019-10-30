#include "vm_corewar.h"

void    	op_aff(t_all *all, t_process *proc)
{
	if (!proc->to_do)
	{
		ft_memcpy(&proc->op, &op_tab[all->map[proc->pc]], sizeof(t_op));
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		parse_arg_op(all, proc);
		ft_putchar((unsigned int)proc->op.params[0] % 256);
		// affiche_new_pc();
	}
	proc->to_do = 1 - proc->to_do;
}
