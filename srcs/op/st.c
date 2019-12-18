/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:53:29 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/14 00:53:31 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		op_st(t_all *all, t_process *p)
{
	int	pc_w;

	pc_w = p->pc;
	if (parse_arg_op(all, p))
	{
		if (p->op.type_of_params[1] == T_IND)
		{
			pc_w = calcul_new_pc_idx(pc_w, p->op.params[1]);
			// move_pc(&pc_w, p->op.params[1] % IDX_MOD);
			all->map.character[pc_w] = (p->reg[*p->op.params - 1] & B4) >> 24;
			change_color(all, p, pc_w);
			move_pc(&pc_w, 1);
			all->map.character[pc_w] = (p->reg[*p->op.params - 1] & B3) >> 16;
			change_color(all, p, pc_w);
			move_pc(&pc_w, 1);
			all->map.character[pc_w] = (p->reg[*p->op.params - 1] & B2) >> 8;
			change_color(all, p, pc_w);
			move_pc(&pc_w, 1);
			all->map.character[pc_w] = (p->reg[*p->op.params - 1] & B1);
			change_color(all, p, pc_w);
		}
		else
			p->reg[p->op.params[1] - 1] =
				p->reg[p->op.params[0] - 1];
	}
}
