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
		parse_arg_op(all, proc);
		if ((unsigned int)proc->op.params[2] > REG_NUMBER ||
			(unsigned int)proc->op.params[1] > REG_NUMBER ||
			(unsigned int)proc->op.params[0] > REG_NUMBER)
			proc->carry = 0;
		else
			proc->reg[proc->op.params[2] - 1] = proc->reg[proc->op.params[0] - 1] - proc->reg[proc->op.params[1] - 1];
	}
	proc->to_do = 1 - proc->to_do;
}
