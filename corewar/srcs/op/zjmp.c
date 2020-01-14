/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:53:38 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/20 14:01:42 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		op_zjmp(t_all *all, t_process *proc)
{
	int		old_pc;

	old_pc = proc->pc;
	if (parse_arg_op(all, proc))
	{
		if (proc->carry)
		{
			if (all->flag & FLAG_RESUME && !(all->flag & FLAG_VISU))
				ft_printf("OK\n");
			proc->pc = calcul_new_pc_idx(old_pc, proc->op.params[0]);
			proc->origin_champ->index_player += 2;
			change_color(all, proc, proc->pc);
			proc->origin_champ->index_player -= 2;
		}
		else if (all->flag & FLAG_RESUME && !(all->flag & FLAG_VISU))
			ft_printf("FAILED\n");
	}
}
