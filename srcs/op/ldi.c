/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:53:09 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/16 18:53:34 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		op_ldi(t_all *all, t_process *proc)
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
			ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
				proc->op.params[0], proc->op.params[1],
				proc->op.params[0] + proc->op.params[1],
				calcul_new_pc_idx(pc, proc->op.params[0] + proc->op.params[1]));
		pc = calcul_new_pc_idx(pc, proc->op.params[0] + proc->op.params[1]);
		proc->reg[proc->op.params[2] - 1] = read_int_in_map(all, pc);
	}
}
