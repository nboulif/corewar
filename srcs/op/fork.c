#include "vm_corewar.h"

void    	op_fork(t_all *all, t_process *proc)
{
	t_champ		*champ;
	t_process	new_proc;
	static int	old_pc;

	old_pc = proc->pc;
	parse_arg_op(all, proc);
	ft_bzero(&new_proc, sizeof(new_proc));
	ft_memcpy((void*)new_proc.reg, proc->reg, sizeof(int) * REG_SIZE);
	new_proc.origin_champ = proc->origin_champ;
	new_proc.carry = proc->carry;
	new_proc.pc = old_pc;
	new_proc.to_do = 0;
	move_pc(&new_proc.pc, proc->op.params[0] % IDX_MOD);
	proc->to_do = 0;
	ft_array_add(all->stack_proc, &new_proc);
}