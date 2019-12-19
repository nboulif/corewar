/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:53:06 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/16 18:29:23 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		op_ld(t_all *all, t_process *proc)
{
	int pc_to_read;

	pc_to_read = proc->pc;
	if (parse_arg_op(all, proc))
	{
		give_value_of_arg(all, proc, pc_to_read, 0);
		proc->reg[proc->op.params[1] - 1] = proc->op.params[0];
		proc->carry = !proc->reg[proc->op.params[1] - 1];
	}
}
