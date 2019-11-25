#include "vm_corewar.h"

void    	op_ld(t_all *all, t_process *proc)
{
	int pc_to_read;

	pc_to_read = proc->pc;
	if (parse_arg_op(all, proc))
	{
		if (proc->op.type_of_params[0] == T_IND)
		{
			// move_pc(&pc_to_read, proc->op.params[0] % IDX_MOD);
			// proc->reg[proc->op.params[1] - 1] = read_int_in_map(all, pc_to_read);

			proc->reg[proc->op.params[1] - 1] = read_int_in_map(all, pc_to_read, IDX_MOD, proc->op.params[0]);
			if (proc->reg[proc->op.params[1] - 1] == -65280)
				fprintf(stderr, "%02hhx %02hhx %02hhx %02hhx\n", (unsigned char)((proc->reg[proc->op.params[1] - 1] & 0xff000000) >> 24), (unsigned char)((proc->reg[proc->op.params[1] - 1] & 0x00ff0000) >> 16), (unsigned char)((proc->reg[proc->op.params[1] - 1] & 0x0000ff00) >> 8), (unsigned char)(proc->reg[proc->op.params[1] - 1] & 0x000000ff));
		}
		else
			proc->reg[proc->op.params[1] - 1] = proc->op.params[0];
		proc->carry = !proc->reg[proc->op.params[1] - 1];
	}
}