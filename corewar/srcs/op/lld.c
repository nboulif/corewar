/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:53:16 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/20 16:00:19 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		op_lld(t_all *all, t_process *proc)
{
	int pc_to_read;

	pc_to_read = proc->pc;
	if (parse_arg_op(all, proc))
	{
		if (proc->op.type_of_params[0] == T_REG)
			proc->op.params[0] = proc->reg[proc->op.params[0] - 1] >> 16;
		else if (proc->op.type_of_params[0] == T_IND)
		{
			pc_to_read = calcul_new_pc(pc_to_read, proc->op.params[0]);
			proc->op.params[0] = read_int_in_map(all, pc_to_read) >> 16;
		}
		proc->reg[proc->op.params[1] - 1] = proc->op.params[0];
		proc->carry = !proc->reg[proc->op.params[1] - 1];
	}
}
