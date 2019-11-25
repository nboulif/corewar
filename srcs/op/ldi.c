#include "vm_corewar.h"

void		config_arg_ldi(t_all *all, t_process *proc, int *p0, int *p1)
//todo delete
{
	if (proc->op.type_of_params[0] == T_REG)
		*p0 = proc->reg[proc->op.params[0] - 1];
	else if (proc->op.params[0] == T_IND)
	{
		*p0 = proc->pc;
		// move_pc(p0, proc->op.params[0] % IDX_MOD);
		// *p0 = read_int_in_map(all, *p0);
		*p0 = read_int_in_map(all, *p0, IDX_MOD, proc->op.params[0]);
	}
	else
		*p0 = proc->op.params[0];
	if (proc->op.type_of_params[1] == T_REG)
		*p1 = proc->reg[proc->op.params[1] - 1];
	else if (proc->op.params[1] == T_IND)
	{
		*p1 = proc->pc;
		// move_pc(p1, proc->op.params[1] % IDX_MOD);
		// *p1 = read_int_in_map(all, *p0);
		*p1 = read_int_in_map(all, *p0, IDX_MOD, proc->op.params[1]);
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
		if (all->flag & FLAG_RESUME && !(all->flag & FLAG_VISU))
			printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
				proc->op.params[0], proc->op.params[1],
				proc->op.params[0] + proc->op.params[1], (pc + (proc->op.params[0] + proc->op.params[1]) % IDX_MOD) % MEM_SIZE);
		// move_pc(&pc, (proc->op.params[0] + proc->op.params[1]) % IDX_MOD);
		// proc->reg[proc->op.params[2] - 1] = read_int_in_map(all, pc);
		p1 = read_int_in_map(all, pc, IDX_MOD, (proc->op.params[0] + proc->op.params[1]));
	}
}
