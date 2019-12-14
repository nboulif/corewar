/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:52:37 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/14 00:52:40 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		op_and(t_all *all, t_process *proc)
{
	int i;
	int param[2];
	int pc_to_read;

	pc_to_read = proc->pc;
	if (parse_arg_op(all, proc))
	{
		config_arg_binary_op(all, proc, pc_to_read);
		proc->reg[proc->op.params[2] - 1] =
			proc->op.params[0] & proc->op.params[1];
		proc->carry = !proc->reg[proc->op.params[2] - 1];
	}
}
