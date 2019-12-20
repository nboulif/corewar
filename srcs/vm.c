/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:32:35 by nsondag           #+#    #+#             */
/*   Updated: 2019/12/20 15:40:35 by nsondag          ###   ########.fr       */
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
	current_process->op = op_tab[(int)all->map.character[current_process->pc]];
	current_process->wait = current_process->op.cycles - 1;
}

int		delete_element(t_all *all, t_process **element, t_process *prev)
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

int		check_nb_live(t_all *all, int total_cycle)
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
				process->index, --total_cycle - process->last_live,
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

void	make_action_and_visu(t_all *all, int total_cycle)
{
	t_process *proc;

	if (all->flag & FLAG_VISU && total_cycle >= 100)
	{
		moveTo(10, 64 * 3 + 20);
		ft_printf("nb_cycle %d die %d %4d", total_cycle,
				all->cycle_to_die, all->nb_process);
		hexdump_map_square(all);
	}
	proc = all->stack_proc;
	while (1)
	{
		if (proc->op.opc == 1 && proc->wait == 1)
			proc->last_live = total_cycle;
		next_action(all, proc);
		if (!(proc = proc->next))
			break ;
	}
}

int		check_ctd(t_all *all, int total_cycle)
{
	static int cycle = 1;

	if (cycle++ >= all->cycle_to_die)
	{
		if (!check_nb_live(all, total_cycle))
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
	}
	return (1);
}

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
}
