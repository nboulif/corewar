#include "vm_corewar.h"

void		config_arg_ldi(t_all *all, t_process *proc, int *p0, int *p1)
{
	if (proc->op.type_of_params[0] == T_REG)
		*p0 = proc->reg[proc->op.params[0] - 1];
	else if (proc->op.params[0] == T_IND)
	{
		*p0 = proc->pc;
		move_pc(p0, proc->op.params[0] % IDX_MOD);
		*p0 = read_int_in_map(all, *p0);
	}
	else
		*p0 = proc->op.params[0];
	if (proc->op.type_of_params[1] == T_REG)
		*p1 = proc->reg[proc->op.params[1] - 1];
	else if (proc->op.params[1] == T_IND)
	{
		*p1 = proc->pc;
		move_pc(p1, proc->op.params[1] % IDX_MOD);
		*p1 = read_int_in_map(all, *p0);
	}
	else
		*p1 = proc->op.params[1];
}

void    	op_ldi(t_all *all, t_process *proc)
{
	int pc;
	int p0;
	int p1;

	pc = proc->pc;
	if (parse_arg_op(all, proc))
	{
		give_value_of_arg(all, proc, pc, 0);
		give_value_of_arg(all, proc, pc, 1);
		proc->reg[proc->op.params[2] - 1] = 0;
		config_arg_ldi(all, proc, &p0, &p1);
		// move_pc(&pc, ((long)proc->op.params[0] + (long)proc->op.params[1]) % IDX_MOD);
		// proc->reg[proc->op.params[2] - 1] |= ((int)(unsigned char)all->map.character[pc]) << 24;
		// pc = proc->pc;
		// move_pc(&pc, ((long)proc->op.params[0] + (long)proc->op.params[1] + 1) % IDX_MOD);
		// proc->reg[proc->op.params[2] - 1] |= ((int)(unsigned char)all->map.character[pc]) << 16;
		// pc = proc->pc;
		// move_pc(&pc, ((long)proc->op.params[0] + (long)proc->op.params[1] + 2) % IDX_MOD);
		// proc->reg[proc->op.params[2] - 1] |= ((int)(unsigned char)all->map.character[pc]) << 8;
		// pc = proc->pc;
		// move_pc(&pc, ((long)proc->op.params[0] + (long)proc->op.params[1] + 3) % IDX_MOD);
		// proc->reg[proc->op.params[2] - 1] |= ((int)(unsigned char)all->map.character[pc]);

		// pc = 0;
		// move_pc(&pc, proc->op.params[0]);
		// move_pc(&pc, proc->op.params[1]);
		proc->reg[proc->op.params[2] - 1] = read_int_in_map(all, pc + p0 + p1);
	}
}
