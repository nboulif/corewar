#include "vm_corewar.h"

void    	op_fork(t_all *all, t_process *proc)
{
	t_champ		*champ;
	t_process	*new_proc;
	static int	old_pc;

	old_pc = proc->pc;
	if (parse_arg_op(all, proc))
	{
		if (all->flag & FLAG_RESUME)
			printf("(%d)\n", proc->op.params[0] % IDX_MOD + old_pc);
		new_proc = malloc(sizeof(t_process));
		ft_bzero(new_proc, sizeof(t_process));
		ft_memcpy(new_proc->reg, proc->reg, sizeof(int) * REG_NUMBER);
		new_proc->origin_champ = proc->origin_champ;
		new_proc->carry = proc->carry;
		new_proc->flag_live = proc->flag_live;
		new_proc->pc = old_pc;
		new_proc->index = ++all->max;
		move_pc(&new_proc->pc, proc->op.params[0] % IDX_MOD);
		new_proc->next = all->stack_proc;
		all->stack_proc = new_proc;
		all->nb_process++;
	}
}
