#include "vm_corewar.h"

void    	op_zjmp(t_all *all, t_process *proc)
{
	int old_pc;
	static int save = 79;

	old_pc = proc->pc;
	parse_arg_op(all, proc);
	if (proc->carry)
	{
		proc->pc = old_pc;
		// moveTo(save++, 10);
		// printf("zjmp %d\n", proc->op.params[0]);
		move_pc(&proc->pc, proc->op.params[0] % IDX_MOD);
	}
	if (save > 90)
		save = 79;
}
