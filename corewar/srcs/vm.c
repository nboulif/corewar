/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:32:35 by nsondag           #+#    #+#             */
/*   Updated: 2020/01/11 19:13:06 by nsondag          ###   ########.fr       */
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
	if ((all->map.character[current_process->pc] < 1 ||
				all->map.character[current_process->pc] > 16))
	{
		move_pc(&current_process->pc, 1);
		return ;
	}
	current_process->op = g_op_tab[(int)all->map.character
		[current_process->pc]];
	current_process->wait = current_process->op.cycles - 1;
}

int			delete_element(t_all *all, t_process **element, t_process *prev)
{
	if (prev)
	{
		prev->next = (*element)->next;
		*element = prev;
	}
	else
	{
		all->stack_proc = (*element)->next;
		*element = all->stack_proc;
		return (1);
	}
	return (0);
}

int			check_nb_live(t_all *all)
{
	t_process		*process;
	t_process		*prev;

	prev = NULL;
	process = all->stack_proc;
	while (process)
	{
		if (!process->flag_live)
		{
			if (all->flag & FLAG_DEATH)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				process->index, --all->total_cycle - process->last_live,
				all->cycle_to_die - CYCLE_DELTA);
			all->nb_process--;
			if (delete_element(all, &process, prev))
				continue ;
		}
		if (process)
			(process->flag_live = 0);
		prev = process;
		if (!process || !(process = process->next))
			break ;
	}
	return (!!all->stack_proc);
}

void		make_action_and_visu(t_all *all)
{
	t_process *proc;

	if (all->flag & FLAG_VISU && all->total_cycle > 1600)
		ncurses_print_screen(all);
	proc = all->stack_proc;
	while (1)
	{
		if (proc->op.opc == 1 && proc->wait == 1)
			proc->last_live = all->total_cycle;
		next_action(all, proc);
		if (!(proc = proc->next))
			break ;
	}
}

int			check_ctd(t_all *all)
{
	static int	cycle = 1;
	size_t		i;

	i = 0;
	if (cycle++ >= all->cycle_to_die)
	{
		if (!check_nb_live(all))
			return (0);
		all->nb_check++;
		if (all->nb_live >= NBR_LIVE || all->nb_check >= MAX_CHECKS)
		{
			if (all->flag & FLAG_CYCLE)
				ft_printf("Cycle to die is now %d\n",
						all->cycle_to_die - CYCLE_DELTA);
			all->cycle_to_die -= CYCLE_DELTA;
			all->nb_check = 0;
		}
		all->nb_live = 0;
		cycle = 1;
		while (i < all->nb_champ)
			all->champ[i++].nb_live_cur_period = 0;
	}
	return (1);
}
