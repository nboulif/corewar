/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:32:35 by nsondag           #+#    #+#             */
/*   Updated: 2019/12/10 22:35:18 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		next_action(t_all *all, t_process *current_process)
{
	if (current_process->wait)
	{
		if (--current_process->wait == 0)
			current_process->op.op(all, current_process);
		return ;
	}
	if ((all->map.character[current_process->pc] < 1 || all->map.character[current_process->pc] > 16))
	{
		move_pc(&current_process->pc, 1);
		return ;
	}
	ft_memcpy(&current_process->op, &op_tab[all->map.character[current_process->pc]], sizeof(t_op));
	current_process->wait = current_process->op.cycles - 1;
}

int		check_nb_live(t_all *all)
{
	static int		first_test = 0;
	t_process		*process;
	int				i;

	i = -1;
	while (++i < all->stack_proc->n_items)
	{
		process = (t_process*)ft_array_get(all->stack_proc, i);
		if (!process->flag_live)
		{
			if (all->flag & FLAG_DEATH)
				printf("Process %d hasn't lived for %d cycles (CTD %d)\n", process->index, all->total_cycle - process->last_live, all->cycle_to_die);
			ft_array_remove(all->stack_proc, i--, NULL);
		}
		else
			process->flag_live = 0;
	}
	return (all->stack_proc->n_items);
}

void		vm(t_all *all)
{
	t_all	*tmp_all;
	int 	cycle;
	int		i;
	cycle = 1;

	init_vm(all);
	while (all->cycles_before_exit == -1 || all->total_cycle < all->cycles_before_exit)
	{
		i = 0;
		if (all->flag & FLAG_VISU && all->total_cycle >= 1500)//!(all->total_cycle % 5))
		{
			moveTo(10, 64 * 3 + 20);
			printf("nb_cycle %d die %d %d", all->total_cycle, all->cycle_to_die, all->stack_proc->n_items);
			hexdump_map_square(all);
		}
		tmp_all = all;
		while (i < all->stack_proc->n_items)
		{
			t_process *tmp_proc = (t_process*)ft_array_get(all->stack_proc, i++);
			if (tmp_proc && tmp_proc->wait == 1 && (tmp_proc->op.opc == 12 || tmp_proc->op.opc == 15))
				i++;
			next_action(all, tmp_proc);
		}
		all->total_cycle++;
		if (all->flag & FLAG_CYCLE)
			printf("It is now cycle %d\n", all->total_cycle);
		if (cycle++ == all->cycle_to_die)
		{
			if (!check_nb_live(all))
				break ;
			all->nb_check++;
			if (all->nb_live >= NBR_LIVE  || all->nb_check >= MAX_CHECKS)
			{
				if (all->flag & FLAG_CYCLE)
					printf("Cycle to die is now %d\n", all->cycle_to_die - CYCLE_DELTA);
				if ((all->cycle_to_die -= CYCLE_DELTA) <= 0)
				{
					if (all->flag & FLAG_CYCLE)
						printf("It is now cycle %d\n", all->total_cycle + 1);
					break;
				}
				all->nb_check = 0;
			}
			all->nb_live = 0;
			cycle = 1;
		}
	}
	if (all->last_player_alive)
		printf("Contestant %d, \"%s\", has won !\n", (-1) * all->last_player_alive->index, all->last_player_alive->name);
	else
		printf("Everybody lost\n");
	if (all->flag & FLAG_DUMP && all->total_cycle == all->cycles_before_exit)
		simple_hexdump(all);
	//while (all->flag & FLAG_VISU)
		//;
}
