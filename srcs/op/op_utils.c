/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:53:24 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/20 16:53:41 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

int		read_int_in_map_idx(t_all *all, int pc, int deplacement)
{
	return (
			(((int)(unsigned char)all->map.character[calcul_new_pc_idx(pc,
																	   deplacement)]) << 24) |
			(((int)(unsigned char)all->map.character[calcul_new_pc_idx(pc,
																	   deplacement + 1)]) << 16) |
			(((int)(unsigned char)all->map.character[calcul_new_pc_idx(pc,
																	   deplacement + 2)]) << 8) |
			((int)(unsigned char)all->map.character[calcul_new_pc_idx(pc,
				deplacement + 3)]));
}

t_process	*proc_alloc(int mode)
{
	static t_process	**memo_proc;
	static int			index = 0;
	static int			i_tab = -1;

	if (!mode)
	{
		while (i_tab >= 0)
			free(memo_proc[i_tab--]);
		free(memo_proc);
		memo_proc = NULL;
		i_tab = -1;
		index = 0;
		return (NULL);
	}
	if (index >= SIZE_BLOCK_MEM || !memo_proc)
	{
		index = 0;
		if (!(memo_proc = realloc(memo_proc, sizeof(t_process*) *
						(++i_tab + 1))) || !(memo_proc[i_tab] =
						malloc(sizeof(t_process) * SIZE_BLOCK_MEM)))
			return (NULL);
	}
	return (&memo_proc[i_tab][index++]);
}

void		config_arg_binary_op(t_all *all, t_process *proc, int pc_to_read)
{
	if (proc->op.type_of_params[0] == T_REG)
		proc->op.params[0] = proc->reg[proc->op.params[0] - 1];
	else if (proc->op.type_of_params[0] == T_IND)
	{
		proc->op.params[0] = read_int_in_map(all,
				calcul_new_pc_idx(pc_to_read, proc->op.params[0]));
	}
	if (proc->op.type_of_params[1] == T_REG)
		proc->op.params[1] = proc->reg[proc->op.params[1] - 1];
	else if (proc->op.type_of_params[1] == T_IND)
	{
		proc->op.params[1] = read_int_in_map(all,
				calcul_new_pc_idx(pc_to_read, proc->op.params[1]));
	}
}

int		value_of_arg(t_all *all, t_process *proc, int pc, int index)
{
	if (proc->op.type_of_params[index] == T_REG)
		return (proc->reg[proc->op.params[index] - 1]);
	else if (proc->op.type_of_params[index] == T_IND)
	{
		pc = calcul_new_pc_idx(pc, proc->op.params[index]);
		return (read_int_in_map(all, pc));
	}
	return (proc->op.params[index]);
}

void	give_value_of_arg(t_all *all, t_process *proc, int pc, int index)
{
	if ((unsigned int)index > 2)
		return ;
	if (proc->op.type_of_params[index] == T_REG)
		proc->op.params[index] = proc->reg[proc->op.params[index] - 1];
	else if (proc->op.type_of_params[index] == T_IND)
	{
		pc = calcul_new_pc_idx(pc, proc->op.params[index]);
		proc->op.params[index] = read_int_in_map(all, pc);
	}
}

void	give_value_of_larg(t_all *all, t_process *proc, int pc, int index)
{
	if ((unsigned int)index > 2)
		return ;
	if (proc->op.type_of_params[index] == T_REG)
		proc->op.params[index] = proc->reg[proc->op.params[index] - 1];
	else if (proc->op.type_of_params[index] == T_IND)
	{
		pc = calcul_new_pc(pc, proc->op.params[index]);
		proc->op.params[index] = read_int_in_map(all, pc);
	}
}
