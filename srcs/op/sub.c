#include "vm_corewar.h"

void    	op_sub(t_all *all, t_process *proc)
{
	if (!proc->to_do)
	{
		ft_memcpy(&proc->op, &op_tab[all->map[proc->pc]], sizeof(t_op));
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		if (parse_arg_op(all, proc))
			proc->reg[proc->op.params[2] - 1] = proc->reg[proc->op.params[0] - 1] - proc->reg[proc->op.params[1] - 1];
	}
	proc->to_do = 1 - proc->to_do;
}
