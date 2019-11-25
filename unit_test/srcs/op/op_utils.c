#include "vm_corewar.h"

void		config_arg_binary_op(t_all *all, t_process *proc, int pc_to_read)
{
	if (proc->op.type_of_params[0] == T_REG)
		proc->op.params[0] = proc->reg[proc->op.params[0] - 1];
	else if (proc->op.type_of_params[0] == T_IND)
	{
		// move_pc(&pc_to_read, proc->op.params[0] % IDX_MOD);
		// proc->op.params[0] = read_int_in_map(all, pc_to_read);
		proc->op.params[0] = read_int_in_map(all, pc_to_read, IDX_MOD, proc->op.params[0]);
	}
	if (proc->op.type_of_params[1] == T_REG)
		proc->op.params[1] = proc->reg[proc->op.params[1] - 1];
	else if (proc->op.type_of_params[1] == T_IND)
	{
		// move_pc(&pc_to_read, proc->op.params[1] % IDX_MOD);
		// proc->op.params[1] = read_int_in_map(all, pc_to_read);
		proc->op.params[1] = read_int_in_map(all, pc_to_read, IDX_MOD, proc->op.params[1]);
	}
}

void    give_value_of_arg(t_all *all, t_process *proc, int pc, int index)
{
	if ((unsigned int)index > 2)
		return ;
	if (proc->op.type_of_params[index] == T_REG)
		proc->op.params[index] = proc->reg[proc->op.params[index] - 1];
	else if (proc->op.type_of_params[index] == T_IND)
	{
		// move_pc(&pc, proc->op.params[index] % IDX_MOD);
		// proc->op.params[index] = read_int_in_map(all, pc);
		proc->op.params[1] = read_int_in_map(all, pc, IDX_MOD, proc->op.params[index]);
	}
}

void    give_value_of_larg(t_all *all, t_process *proc, int pc, int index)
{
	if ((unsigned int)index > 2)
		return ;
	if (proc->op.type_of_params[index] == T_REG)
		proc->op.params[index] = proc->reg[proc->op.params[index] - 1];
	else if (proc->op.type_of_params[index] == T_IND)
	{
		// move_pc(&pc, proc->op.params[index]);
		// proc->op.params[index] = read_int_in_map(all, pc);
		// proc->op.params[index] = read_int_in_map(all, pc);
		proc->op.params[1] = read_int_in_map(all, pc, INT_MAX, proc->op.params[index]);
	}
}