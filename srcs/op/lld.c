#include "vm_corewar.h"

void    	op_lld(t_all *all, t_process *proc)
{
	int pc_to_read;

	pc_to_read = proc->pc;
	if (parse_arg_op(all, proc))
	{
		if (proc->op.type_of_params[0] == T_IND)
		{	
			give_value_of_larg(all, proc, pc_to_read, 0);
			proc->reg[proc->op.params[1] - 1] = proc->op.params[0];
		}
		else
			proc->reg[proc->op.params[1] - 1] = proc->op.params[0];
		proc->carry = !proc->reg[proc->op.params[1] - 1];
	}
}
