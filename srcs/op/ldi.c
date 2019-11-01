#include "vm_corewar.h"

void    	op_ldi(t_all *all, t_process *proc)
{
	int pc;

	if (!proc->to_do)
	{
		ft_memcpy(&proc->op, &op_tab[all->map[proc->pc]], sizeof(t_op));
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		pc = proc->pc;
		if (parse_arg_op(all, proc))
		{
			move_pc(&pc, ((long)proc->op.params[0] + (long)proc->op.params[1]) % IDX_MOD);
			// pc = 0;
			// move_pc(&pc, proc->op.params[0]);
			// move_pc(&pc, proc->op.params[1]);
			proc->reg[proc->op.params[2] - 1] = all->map[pc];
		}
	}
	proc->to_do = 1 - proc->to_do;
}
