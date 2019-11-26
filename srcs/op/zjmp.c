#include "vm_corewar.h"

void    	op_zjmp(t_all *all, t_process *proc)
{
	int old_pc;
	char *to_print;

	old_pc = proc->pc;
	if (parse_arg_op(all, proc))
	{
		if (proc->carry)
		{
			proc->pc = old_pc;
			if (all->flag & FLAG_RESUME && !(all->flag & FLAG_VISU))
				printf("OK\n");
			move_pc(&proc->pc, proc->op.params[0] % IDX_MOD);
		}
		else if (all->flag & FLAG_RESUME && !(all->flag & FLAG_VISU))
			printf("FAILED\n");
	}
}
