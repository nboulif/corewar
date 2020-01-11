/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 16:37:29 by nsondag           #+#    #+#             */
/*   Updated: 2020/01/11 16:38:00 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		free_all(t_all *all, t_process *first_process)
{
	proc_alloc(0);
	free(first_process);
	while (all->nb_champ--)
	{
		free(all->champ[all->nb_champ].name);
		free(all->champ[all->nb_champ].comment);
		free(all->champ[all->nb_champ].exec_code);
	}
	free(all->map.character);
	free(all->map.color_in_map);
}

void		vm(t_all *all)
{
	int			total_cycle;
	t_process	*first_process;

	total_cycle = 0;
	init_vm(all);
	first_process = all->stack_proc;
	while (all->cycles_before_exit == -1 ||
			total_cycle < all->cycles_before_exit)
	{
		make_action_and_visu(all, total_cycle++);
		if (all->flag & FLAG_CYCLE)
			ft_printf("It is now cycle %d\n", total_cycle);
		if (!check_ctd(all, total_cycle))
			break ;
	}
	if (all->last_player_alive)
		ft_printf("Contestant %d, \"%s\", has won !\n",
				(-1) * all->last_player_alive->index,
				all->last_player_alive->name);
	else
		ft_printf("Everybody lost\n");
	if (((all->flag & FLAG_DUMP) || (all->flag & FLAG_DUMP64))
			&& total_cycle == all->cycles_before_exit)
		(all->flag & FLAG_DUMP) ? simple_hexdump(all, 32) :
			simple_hexdump(all, 64);
	free_all(all, first_process);
}
