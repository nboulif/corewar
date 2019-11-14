#include "vm_corewar.h"

void    	op_lldi(t_all *all, t_process *proc)
{
	int pc;

	// printf("ici\n");
	pc = proc->pc;
	if (parse_arg_op(all, proc))
	{
		// if (proc->op.params[2] > REG_NUMBER || proc->op.params[2] < 1)
		// 	return ;
		// give_value_of_arg(all, proc, pc, 0);
		// give_value_of_arg(all, proc, pc, 1);
		give_value_of_larg(all, proc, pc, 0);
		give_value_of_larg(all, proc, pc, 1);
		// printf("la\n");
		move_pc(&pc, ((long)proc->op.params[0] + (long)proc->op.params[1]) % MEM_SIZE);
		char c = all->map.character[pc];
		// printf("ca passe %d\n", proc->op.params[2]);
		proc->reg[proc->op.params[2] - 1] = c;
	}
}
