#include "vm_corewar.h"

void    	op_ldi(t_all *all, t_process *proc)
{
	int pc;

	if (!proc->to_do)
	{
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		parse_arg_op(all, proc);
		if (proc->op.params[2] <= REG_NUMBER && proc->op.params[2] > 0)
		{
			pc = ((long)proc->op.params[0] + (long)proc->op.params[1]) % IDX_MOD;
			// pc = 0;
			// move_pc(&pc, proc->op.params[0]);
			// move_pc(&pc, proc->op.params[1]);
			proc->reg[proc->op.params[2] - 1] = all->map[pc];
		}
		else 
			proc->carry = 0;
	}
	proc->to_do = 1 - proc->to_do;
}
