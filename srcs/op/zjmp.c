#include "vm_corewar.h"

void    	op_zjmp(t_all *all, t_process *proc)
{
	int old_pc;
	static int save = 79;

	if (!proc->to_do)
	{
		ft_memcpy(&proc->op, &op_tab[all->map[proc->pc]], sizeof(t_op));
		proc->wait = proc->op.cycles - 1;
		//printf("zjmp prepa %d\n", proc->op.params[0]);
	}
	else
	{
		old_pc = proc->pc;
		parse_arg_op(all, proc);
		// printf("zjump\n");
		if (proc->carry)
		{
			proc->pc = old_pc;
			// moveTo(save++, 10);
			// printf("zjmp %d\n", proc->op.params[0]);
			move_pc(&proc->pc, proc->op.params[0] % IDX_MOD);
		}
		else
		{
			// moveTo(save++, 10);
			// printf("!! carrry == 0 !!\n");
		}
		
	}
	if (save > 90)
		save = 79;
	proc->to_do = 1 - proc->to_do;
}
