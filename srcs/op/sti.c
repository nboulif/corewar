/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:53:31 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/15 18:08:38 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

int			calcul_new_pc_idx(int pc, int deplacement)
{
	if (deplacement <= -MEM_SIZE || deplacement >= MEM_SIZE)
		deplacement %= MEM_SIZE;
	pc += (deplacement % IDX_MOD);
	if (pc < 0)
		pc += MEM_SIZE;
	return (pc % MEM_SIZE);
}

int			calcul_new_pc(int pc, int deplacement)
{
	if (deplacement <= -MEM_SIZE || deplacement >= MEM_SIZE)
		deplacement %= MEM_SIZE;
	pc += deplacement;
	if (pc < 0)
		pc += MEM_SIZE;
	return (pc % MEM_SIZE);
}

void		config_arg_sti_and_resume(t_all *all, t_process *proc, int pc_to_write)
{
	int pc_to_read;

	if (proc->op.type_of_params[1] == T_REG)
	{
		proc->op.params[1] = proc->reg[proc->op.params[1] - 1];
	}
	else if (proc->op.type_of_params[1] == T_IND)
	{
		pc_to_read = pc_to_write;
		// move_pc(&pc_to_read, proc->op.params[1] % IDX_MOD);
		pc_to_read = calcul_new_pc_idx(pc_to_read, proc->op.params[1]);
		proc->op.params[1] = read_int_in_map(all, pc_to_read);
	}
	if (proc->op.type_of_params[2] == T_REG)
		proc->op.params[2] = proc->reg[proc->op.params[2] - 1];
	proc->op.params[0] = proc->reg[proc->op.params[0] - 1];
	if (all->flag & FLAG_RESUME)
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
		proc->op.params[1] , proc->op.params[2],
		proc->op.params[1] + proc->op.params[2],
		(pc_to_write + proc->op.params[1] +
		proc->op.params[2]) % MEM_SIZE);
}

void		op_sti(t_all *all, t_process *proc)
{
	int	pc_to_write;

	pc_to_write = proc->pc;
	if (parse_arg_op(all, proc))
	{
		config_arg_sti_and_resume(all, proc, pc_to_write);
		// move_pc(&pc_to_write,
		// ((int)proc->op.params[1] + (int)proc->op.params[2]) % IDX_MOD);
		pc_to_write = calcul_new_pc_idx(pc_to_write, proc->op.params[1] + proc->op.params[2]);
		all->map.character[pc_to_write] = (proc->op.params[0] & B4) >> 24;
		change_color(all, proc, pc_to_write);
		move_pc(&pc_to_write, 1);
		all->map.character[pc_to_write] = (proc->op.params[0] & B3) >> 16;
		change_color(all, proc, pc_to_write);
		move_pc(&pc_to_write, 1);
		all->map.character[pc_to_write] = (proc->op.params[0] & B2) >> 8;
		change_color(all, proc, pc_to_write);
		move_pc(&pc_to_write, 1);
		all->map.character[pc_to_write] = proc->op.params[0] & B1;
		change_color(all, proc, pc_to_write);
	}
}
