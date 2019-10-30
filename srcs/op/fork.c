#include "vm_corewar.h"

void    	op_fork(t_all *all, t_process *proc)
{
	t_champ		*champ;
	t_process	new_proc;
	static int	old_pc;

	if (!proc->to_do)
	{
		old_pc = proc->pc;
		parse_arg_op(all, proc);
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		ft_bzero(&new_proc, sizeof(new_proc));
		ft_memcpy((void*)new_proc.reg, proc->reg, sizeof(proc->reg));
		new_proc.origin_champ = proc->origin_champ;
		new_proc.carry = proc->carry;
		new_proc.pc = old_pc;
		move_pc(&new_proc.pc, proc->op.params[0] % IDX_MOD);
		ft_array_add(all->stack_proc, &new_proc);
	}
	proc->to_do = 1 - proc->to_do;
}