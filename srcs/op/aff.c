#include "vm_corewar.h"

void    	op_aff(t_all *all, t_process *proc)
{
	if (parse_arg_op(all, proc) && !(all->flag & FLAG_VISU) && !(all->flag & FLAG_RESUME))
		ft_putchar((unsigned int)proc->op.params[0] % 256);
}
