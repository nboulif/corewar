/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:53:13 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/14 00:53:15 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		op_live(t_all *all, t_process *proc)
{
	t_champ	*champ;

	parse_arg_op(all, proc);
	champ = get_champ(proc->op.params[0], all);
	proc->flag_live = 1;
	all->nb_live++;
	if (champ)
		all->last_player_alive = champ;
}
