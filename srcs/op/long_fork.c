#include "vm_corewar.h"

void    	op_longfork(t_all *all, t_process *proc)
{
	t_champ		*champ;
	t_process	new_proc;
	static int	old_pc;

	if (!proc->to_do)
	{
		ft_memcpy(&proc->op, &op_tab[all->map[proc->pc]], sizeof(t_op));
		proc->wait = proc->op.cycles - 1;
		proc->to_do = 1;	
	}
	else
	{
		if (all->flag & FLAG_RESUME)
			printf("champ %d(%s) make a lfork\n", proc->origin_champ->index, proc->origin_champ->name);
		old_pc = proc->pc;
		parse_arg_op(all, proc);
		ft_bzero(&new_proc, sizeof(new_proc));
		ft_memcpy((void*)new_proc.reg, proc->reg, REG_NUMBER);
		new_proc.origin_champ = proc->origin_champ;
		new_proc.carry = proc->carry;
		new_proc.pc = old_pc;
		move_pc(&new_proc.pc, proc->op.params[0]);
		proc->to_do = 0;	
		ft_array_add(all->stack_proc, &new_proc);
	}
}