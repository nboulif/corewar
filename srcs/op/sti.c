#include "vm_corewar.h"

void    	op_sti(t_all *all, t_process *proc)
{
	int	pc_to_write;

	if (!proc->to_do)
	{
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		parse_arg_op(all, proc);
		if (proc->op.type_of_params[0] == T_REG)
		{
			if (proc->op.params[0] < 1 || proc->op.params[0] > REG_NUMBER)
			{
				proc->to_do = 0;
				return ;
			}
			proc->op.params[0] = proc->reg[proc->op.params[0] - 1];
		}
		//// printf("sti print->:\n");
		pc_to_write = 0;

		move_pc(&pc_to_write, ((long)proc->op.params[1] + (long)proc->op.params[2]) % IDX_MOD);
		// move_pc(&pc_to_write, proc->op.params[1]);
		// move_pc(&pc_to_write, proc->op.params[2]);
		all->map[pc_to_write] = (proc->op.params[0] & 0xff000000) >> 24;
		//printf("%.2x ", all->map[pc_to_write]);
		move_pc(&pc_to_write, 1);
		all->map[pc_to_write] = (proc->op.params[0] & 0xff0000) >> 16;
		//printf("%.2x ", all->map[pc_to_write]);
		move_pc(&pc_to_write, 1);
		all->map[pc_to_write] = (proc->op.params[0] & 0xff00) >> 8;
		//printf("%.2x ", all->map[pc_to_write]);
		move_pc(&pc_to_write, 1);
		all->map[pc_to_write] = proc->op.params[0] & 0xff;
		//printf("%.2x\n", all->map[pc_to_write]);
	}
	proc->to_do = 1 - proc->to_do;
}