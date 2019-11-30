#include "vm_corewar.h"

void    	op_longfork(t_all *all, t_process *proc)
{
	t_champ		*champ;
	t_process	new_proc;
	static int	old_pc;

	old_pc = proc->pc;
	if (parse_arg_op(all, proc))
	{
		if (all->flag & FLAG_RESUME)
			printf("(%d)\n", proc->op.params[0] + old_pc);
		ft_bzero(&new_proc, sizeof(new_proc));
		ft_memcpy((void*)new_proc.reg, proc->reg, sizeof(int) * REG_NUMBER);
		new_proc.origin_champ = proc->origin_champ;
		new_proc.carry = proc->carry;
		new_proc.pc = old_pc;
		new_proc.index = ++all->max;
		new_proc.flag_live = proc->flag_live;
		new_proc.last_live = proc->last_live;
		move_pc(&new_proc.pc, proc->op.params[0]);
		ft_array_insert(all->stack_proc, 0, &new_proc);
	}
}
