#include "vm_corewar.h"

void    	op_ld(t_all *all, t_process *proc)
{
	if (!proc->to_do)
	{
		parse_arg_op(all, proc);
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		if ((unsigned int)proc->op.params[1] > REG_NUMBER)
			proc->carry = 0;
		else
			proc->reg[proc->op.params[1] - 1] = proc->op.params[0] % IDX_MOD;
	}
	proc->to_do = 1 - proc->to_do;
}