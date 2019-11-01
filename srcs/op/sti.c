#include "vm_corewar.h"

void    	op_sti(t_all *all, t_process *proc)
{
	int	pc_to_write;
	int old_pc;

	if (!proc->to_do)
	{
		ft_memcpy(&proc->op, &op_tab[all->map[proc->pc]], sizeof(t_op));
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		old_pc = proc->pc;
		if (parse_arg_op(all, proc))
		{
			// int i = -1;
			pc_to_write = old_pc;
			// moveTo(0, 0);
			moveTo(80, 0);
			// printf("sti params: |%ld| |%ld|\n", (long)proc->op.params[1], (long)proc->op.params[2]);
			move_pc(&pc_to_write, ((long)proc->op.params[1] + (long)proc->op.params[2]) % IDX_MOD);
			// move_pc(&pc_to_write, old_pc);
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
	}
	proc->to_do = 1 - proc->to_do;
}