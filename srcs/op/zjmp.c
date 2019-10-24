#include "vm_corewar.h"

void    	op_zjmp(t_all *all, t_process *proc)
{
	if (!proc->to_do)
	{
		parse_arg_op(all, proc);
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		if (proc->carry)
		{
			proc->pc = 0;
			printf("zjmp %d\n", proc->op.params[0]);
			move_pc(&proc->pc, proc->op.params[0] % IDX_MOD);
		}
	}
	proc->to_do = 1 - proc->to_do;
}
