#include "vm_corewar.h"

void    	op_st(t_all *all, t_process *proc)
{
	int	pc_to_write;
	int p1;

	pc_to_write = proc->pc;
	if (parse_arg_op(all, proc))
	{
		if (proc->op.type_of_params[1] == T_IND)
		{
			move_pc(&pc_to_write, proc->op.params[1] % IDX_MOD);
			all->map.character[pc_to_write] = (proc->reg[proc->op.params[0] - 1] & 0xff000000) >> 24;
			change_color(all, proc, pc_to_write);
			move_pc(&pc_to_write, 1);
			all->map.character[pc_to_write] = (proc->reg[proc->op.params[0] - 1] & 0x00ff0000) >> 16;
			change_color(all, proc, pc_to_write);
			move_pc(&pc_to_write, 1);
			all->map.character[pc_to_write] = (proc->reg[proc->op.params[0] - 1] & 0x0000ff00) >> 8;
			change_color(all, proc, pc_to_write);
			move_pc(&pc_to_write, 1);
			all->map.character[pc_to_write] = (proc->reg[proc->op.params[0] - 1] & 0x000000ff);
			change_color(all, proc, pc_to_write);
		}
		else
			proc->reg[proc->op.params[1] - 1] = proc->reg[proc->op.params[0] - 1];
	}
}