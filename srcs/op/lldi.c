#include "vm_corewar.h"

void    	op_lldi(t_all *all, t_process *proc)
{
	int pc;

	if (!proc->to_do)
	{
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		parse_arg_op(all, proc);
		if (proc->op.params[2] <= REG_NUMBER && proc->op.params[2] > 0 &&
			proc->op.params[0] < MEM_SIZE &&
			proc->op.params[1] < MEM_SIZE &&
			proc->op.params[0] + proc->op.params[1] < MEM_SIZE)
		{
			pc = proc->op.params[0] + proc->op.params[1];
			proc->reg[proc->op.params[2] - 1] = all->map[pc];
		}
		else 
			proc->carry = 0;
	}
	proc->to_do = 1 - proc->to_do;
}
