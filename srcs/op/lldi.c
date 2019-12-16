/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lldi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:53:19 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/16 18:36:34 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		op_lldi(t_all *all, t_process *proc)
{
	int		pc;

	pc = proc->pc;
	if (parse_arg_op(all, proc))
	{
		if (proc->op.params[2] > REG_NUMBER || proc->op.params[2] < 1)
			return ;
		give_value_of_larg(all, proc, pc, 0);
		give_value_of_larg(all, proc, pc, 1);
		if (all->flag & FLAG_RESUME && !(all->flag & FLAG_VISU))
			ft_printf("       | -> load from %d + %d = %d (with pc and mod %ld)\n",
				proc->op.params[0], proc->op.params[1],
				proc->op.params[0] + proc->op.params[1], ((long)pc +
					(long)proc->op.params[0] + (long)proc->op.params[1]));
		move_pc(&pc, (long)proc->op.params[0] + (long)proc->op.params[1]);
		proc->reg[proc->op.params[2] - 1] = all->map.character[pc];
		proc->carry = !proc->reg[proc->op.params[2] - 1];
	}
}
