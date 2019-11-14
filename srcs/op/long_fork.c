#include "vm_corewar.h"

void    	op_longfork(t_all *all, t_process *proc)
{
	t_champ		*champ;
	t_process	new_proc;
	static int	old_pc;

	if (all->flag & FLAG_RESUME)
		printf("champ %d(%s) make a lfork\n", proc->origin_champ->index, proc->origin_champ->name);
	old_pc = proc->pc;
	if (!parse_arg_op(all, proc))
	{
		ft_bzero(&new_proc, sizeof(new_proc));
		ft_memcpy((void*)new_proc.reg, proc->reg, sizeof(int) * REG_NUMBER);
		new_proc.origin_champ = proc->origin_champ;
		new_proc.carry = proc->carry;
		new_proc.pc = old_pc;
		move_pc(&new_proc.pc, proc->op.params[0]);
		// proc->to_die = 0;	
		//ft_array_add(all->stack_proc, &new_proc);
		ft_array_insert(all->stack_proc, 0, &new_proc);
		//printf("size %d\n", all->stack_proc->size);
	}
}