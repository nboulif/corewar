/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:53:19 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/20 14:12:08 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		op_lldi(t_all *all, t_process *proc)
{
	int		pc;

	pc = proc->pc;
	if (parse_arg_op(all, proc))
	{
		give_value_of_larg(all, proc, pc, 0);
		give_value_of_larg(all, proc, pc, 1);
		if (all->flag & FLAG_RESUME && !(all->flag & FLAG_VISU))
			ft_printf("       | -> load from %d + %d = %d
					(with pc and mod %ld)\n",
				proc->op.params[0], proc->op.params[1],
				proc->op.params[0] + proc->op.params[1], ((long)pc +
					(long)proc->op.params[0] + (long)proc->op.params[1]));
		pc = calcul_new_pc(pc, proc->op.params[0] + proc->op.params[1]);
		proc->reg[proc->op.params[2] - 1] = read_int_in_map(all, pc);
		proc->carry = !proc->reg[proc->op.params[2] - 1];
	}
}
