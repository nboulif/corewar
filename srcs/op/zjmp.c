#include "vm_corewar.h"

void    	op_zjmp(t_all *all, t_process *proc)
{
	static int old_pc;

	if (!proc->to_do)
	{
		proc->wait = proc->op.cycles - 1;
		//printf("zjmp prepa %d\n", proc->op.params[0]);
	}
	else
	{
		old_pc = proc->pc;
		parse_arg_op(all, proc);
		if (proc->carry)
		{
			proc->pc = old_pc;
			//printf("zjmp %d\n", proc->op.params[0]);
			move_pc(&proc->pc, proc->op.params[0] % IDX_MOD);
		}
	}
	proc->to_do = 1 - proc->to_do;
}
