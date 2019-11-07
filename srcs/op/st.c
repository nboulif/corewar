#include "vm_corewar.h"

void    	op_st(t_all *all, t_process *proc)
{
	int	pc_to_write;

	if (!proc->to_do)
	{
		parse_arg_op(all, proc);
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		pc_to_write = 0;
		move_pc(&pc_to_write, proc->op.params[1]);
		all->map[pc_to_write] = proc->op.params[0] & 0xff000000;
		move_pc(&pc_to_write, 1);
		all->map[pc_to_write] = proc->op.params[0] & 0xff0000;
		move_pc(&pc_to_write, 1);
		all->map[pc_to_write] = proc->op.params[0] & 0xff00;
		move_pc(&pc_to_write, 1);
		all->map[pc_to_write] = proc->op.params[0] & 0xff;
	}
	proc->to_do = 1 - proc->to_do;
}