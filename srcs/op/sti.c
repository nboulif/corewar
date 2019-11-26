#include "vm_corewar.h"

void    	op_sti(t_all *all, t_process *proc)
{
	int	pc_to_write;
	int old_pc;
	int pc_to_read;

	old_pc = proc->pc;
	if (parse_arg_op(all, proc))
	{
		pc_to_write = old_pc;

		if (proc->op.type_of_params[1] == T_REG)
		{
			proc->op.params[1] = proc->reg[proc->op.params[1] - 1];
		}
		// tester enlevant le else if
		else if (proc->op.type_of_params[1] == T_IND)
		{
			pc_to_read = old_pc;
			move_pc(&pc_to_read, proc->op.params[1] % IDX_MOD);
			proc->op.params[1] = read_int_in_map(all, pc_to_read);
		}
		if (proc->op.type_of_params[2] == T_REG)
		{
			proc->op.params[2] = proc->reg[proc->op.params[2] - 1];
		}
		proc->op.params[0] = proc->reg[proc->op.params[0] - 1];
		if (all->flag & FLAG_RESUME)
			printf("       | -> store to %d + %d = %d (with pc and mod %d)\n", proc->op.params[1] , proc->op.params[2], proc->op.params[1] + proc->op.params[2], pc_to_write + proc->op.params[1] + proc->op.params[2]);
		move_pc(&pc_to_write, ((long)proc->op.params[1] + (long)proc->op.params[2]) % IDX_MOD);
		// moveTo(50, 64 * 3 + 20);
		// printf("pc_to_write %d proc->op.params[0] %x\n", pc_to_write, proc->op.params[0]);
		all->map.character[pc_to_write] = (proc->op.params[0] & 0xff000000) >> 24;
		change_color(all, proc, pc_to_write);
		move_pc(&pc_to_write, 1);
		all->map.character[pc_to_write] = (proc->op.params[0] & 0xff0000) >> 16;
		change_color(all, proc, pc_to_write);		
		move_pc(&pc_to_write, 1);
		all->map.character[pc_to_write] = (proc->op.params[0] & 0xff00) >> 8;
		change_color(all, proc, pc_to_write);		
		move_pc(&pc_to_write, 1);
		all->map.character[pc_to_write] = proc->op.params[0] & 0xff;
		change_color(all, proc, pc_to_write);
	}
}
