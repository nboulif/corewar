#include "vm_corewar.h"

void    	op_st(t_all *all, t_process *proc)
{
	int	pc_to_write;

	if (!proc->to_do)
	{
		printf("ici (%d)\n", proc->pc);
		ft_memcpy(&proc->op, &op_tab[all->map[proc->pc]], sizeof(t_op));
		proc->wait = proc->op.cycles - 1;
		printf("la\n");

	}
	else
	{
		pc_to_write = proc->pc;
		if (parse_arg_op(all, proc))
		{
			ft_putstr("ici part 2\n\n");
			move_pc(&pc_to_write, proc->op.params[1]);
			printf("pc_to_write (%d)\n", pc_to_write);
			all->map[pc_to_write] = proc->op.params[0] & 0xff000000;
			move_pc(&pc_to_write, 1);
			printf("pc_to_write (%d)\n", pc_to_write);
			all->map[pc_to_write] = proc->op.params[0] & 0xff0000;
			move_pc(&pc_to_write, 1);
			printf("pc_to_write (%d)\n", pc_to_write);
			all->map[pc_to_write] = proc->op.params[0] & 0xff00;
			move_pc(&pc_to_write, 1);
			printf("pc_to_write (%d)\n", pc_to_write);
			all->map[pc_to_write] = proc->op.params[0] & 0xff;
			printf("la part 2\n");
		}
	}
	proc->to_do = 1 - proc->to_do;
}