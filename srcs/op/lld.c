/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:53:16 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/14 00:53:18 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		op_lld(t_all *all, t_process *proc)
{
	int pc_to_read;

	pc_to_read = proc->pc;
	// moveTo(80,10);
	// printf("%02hhx %02hhx\n", all->map.character[proc->pc], all->map.character[proc->pc + 1]);
	if (parse_arg_op(all, proc))
	{
		give_value_of_larg(all, proc, pc_to_read, 0);
		proc->reg[proc->op.params[1] - 1] = proc->op.params[0] >> 16;
		proc->carry = !proc->reg[proc->op.params[1] - 1];
	}
}
