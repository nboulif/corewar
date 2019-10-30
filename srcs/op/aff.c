#include "vm_corewar.h"

void    	op_aff(t_all *all, t_process *proc)
{
	if (!proc->to_do)
	{
		parse_arg_op(all, proc);
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		ft_putchar((unsigned int)proc->op.params[0] % 256);
		// affiche_new_pc();
	}
	proc->to_do = 1 - proc->to_do;
}
