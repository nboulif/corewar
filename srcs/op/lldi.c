#include "vm_corewar.h"

void    	op_lldi(t_all *all, t_process *proc)
{
	int pc;

	pc = proc->pc;
	if (parse_arg_op(all, proc))
	{
		give_value_of_arg(all, proc, pc, 0);
		give_value_of_arg(all, proc, pc, 1);
		// give_value_of_larg(all, proc, pc, 0);
		// give_value_of_larg(all, proc, pc, 1);
		move_pc(&pc, ((long)proc->op.params[0] + (long)proc->op.params[1]) % MEM_SIZE);
		proc->reg[proc->op.params[2] - 1] = all->map.character[pc];
	}
}
