/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:53:24 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/14 00:53:25 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

#define SIZE_BLOCK_MEM 50000

t_process *proc_alloc(int mode)
{
	static t_process **memo_proc;
	static int index = 0;
	static int i_tab = 0;

	if (!mode)
	{
		while (i_tab >= 0)
			free(memo_proc[i_tab--]);
		free(memo_proc);
		memo_proc = NULL;
		index = 0;
		i_tab = 0;
		return (NULL);
	}
	if (index > SIZE_BLOCK_MEM)
	{
		index = 0;
		memo_proc = realloc(memo_proc, sizeof(t_process*) * (++i_tab + 1));
		memo_proc[i_tab] = malloc(sizeof(t_process) * SIZE_BLOCK_MEM);
	}
	else if (!memo_proc)
	{
		memo_proc = malloc(sizeof(t_process*));
		memo_proc[0] = malloc(sizeof(t_process) * SIZE_BLOCK_MEM);
	}
	return (&memo_proc[i_tab][index++]);
}

void		config_arg_binary_op(t_all *all, t_process *proc, int pc_to_read)
{
	if (proc->op.type_of_params[0] == T_REG)
		proc->op.params[0] = proc->reg[proc->op.params[0] - 1];
	else if (proc->op.type_of_params[0] == T_IND)
	{
		move_pc(&pc_to_read, proc->op.params[0] % IDX_MOD);
		proc->op.params[0] = read_int_in_map(all, pc_to_read);
	}
	if (proc->op.type_of_params[1] == T_REG)
		proc->op.params[1] = proc->reg[proc->op.params[1] - 1];
	else if (proc->op.type_of_params[1] == T_IND)
	{
		move_pc(&pc_to_read, proc->op.params[1] % IDX_MOD);
		proc->op.params[1] = read_int_in_map(all, pc_to_read);
	}
}

int    value_of_arg(t_all *all, t_process *proc, int pc, int index)
{
	if (proc->op.type_of_params[index] == T_REG)
		return (proc->reg[proc->op.params[index] - 1]);
	else if (proc->op.type_of_params[index] == T_IND)
	{
		move_pc(&pc, proc->op.params[index] % IDX_MOD);
		return (read_int_in_map(all, pc));
	}
	return (proc->op.params[index]);
}

void    give_value_of_arg(t_all *all, t_process *proc, int pc, int index)
{
	if ((unsigned int)index > 2)
		return ;
	if (proc->op.type_of_params[index] == T_REG)
		proc->op.params[index] = proc->reg[proc->op.params[index] - 1];
	else if (proc->op.type_of_params[index] == T_IND)
	{
		move_pc(&pc, proc->op.params[index] % IDX_MOD);
		proc->op.params[index] = read_int_in_map(all, pc);
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
		move_pc(&pc, proc->op.params[index]);
		proc->op.params[index] = read_int_in_map(all, pc);
	}
}
