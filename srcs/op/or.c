#include "vm_corewar.h"

void    	op_or(t_all *all, t_process *proc)
{
	if (!proc->to_do)
	{
		parse_arg_op(all, proc);
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		if ((unsigned int)proc->op.params[2] > REG_NUMBER ||
			(unsigned int)proc->op.params[1] > REG_NUMBER ||
			(unsigned int)proc->op.params[0] > REG_NUMBER)
			proc->carry = 0;
		else
			proc->reg[proc->op.params[2] - 1] = proc->reg[proc->op.params[0] - 1] | proc->reg[proc->op.params[1] - 1];
	}
	proc->to_do = 1 - proc->to_do;
}
