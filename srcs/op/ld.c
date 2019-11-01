#include "vm_corewar.h"

void    	op_ld(t_all *all, t_process *proc)
{
	int pc_to_read;

	if (!proc->to_do)
	{
		ft_memcpy(&proc->op, &op_tab[all->map[proc->pc]], sizeof(t_op));
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		pc_to_read = proc->pc;
		parse_arg_op(all, proc);
		if (proc->op.params[1] <= REG_NUMBER && proc->op.params[1] > 0)
		{
			if (proc->op.type_of_params[0] == T_IND)
			{
				proc->reg[proc->op.params[1] - 1] = 0;
				move_pc(&pc_to_read, proc->op.params[0] % IDX_MOD);
				proc->reg[proc->op.params[1] - 1] |= ((int)(unsigned char)all->map[pc_to_read]) << 24;
				move_pc(&pc_to_read, 1);
				proc->reg[proc->op.params[1] - 1] |= ((int)(unsigned char)all->map[pc_to_read]) << 16;
				move_pc(&pc_to_read, 1);
				proc->reg[proc->op.params[1] - 1] |= ((int)(unsigned char)all->map[pc_to_read]) << 8;
				move_pc(&pc_to_read, 1);
				proc->reg[proc->op.params[1] - 1] |= (int)(unsigned char)all->map[pc_to_read];
			}
			else
				proc->reg[proc->op.params[1] - 1] = proc->op.params[0];
			proc->carry = !proc->reg[proc->op.params[1] - 1];
		}
		else
			proc->carry = 0;
	}
	proc->to_do = 1 - proc->to_do;
}