/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:32:35 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/27 16:04:39 by nsondag          ###   ########.fr       */
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

int		check_nb_live(t_all *all, int total_cycle)
{
	t_process		*process;
	t_process		*prev;
	int				i;
	static int tab_death[500000] = {0};

	i = -1;
	prev = NULL;
	process = all->stack_proc;
	while (1)
	{
		if (!process->flag_live)
		{
			if (all->flag & FLAG_DEATH)
				printf("Process %d hasn't lived for %d cycles (CTD %d)\n", process->index, total_cycle - process->last_live - 1, all->cycle_to_die - CYCLE_DELTA);
			if (tab_death[process->index])
				printf("Process %d double death\n", process->index);
			tab_death[process->index] = 1;
			// printf("lst_proc (delete p%4d prev %4d)", process->index, prev ? prev->index : 0);
			// for (t_process *cur = all->stack_proc; cur && printf(" -> "); cur = cur->next)
			// 	printf("%d", cur->index);
			// printf("\n");
			if (prev)
			{
				prev->next = process->next;
				process = prev;
			}
			else
			{
				all->stack_proc = process->next;
				process = all->stack_proc;
			}
			// printf("                                ");
			// for (t_process *cur = all->stack_proc; cur && printf(" -> "); cur = cur->next)
			// 		printf("%d", cur->index);
			// 	printf("\n");
			all->nb_process--;
		}
		else
			process->flag_live = 0;
		if (!process)
			break;
		prev = process;
		if (!(process = process->next))
			break ;
	}
	return (!!all->stack_proc);
}

void	make_action_and_visu(t_all *all, int total_cycle)
{
	t_process *proc;

	if (all->flag & FLAG_VISU && total_cycle >= 10000)// && !(total_cycle % 5))
	{
		moveTo(10, 64 * 3 + 20);
		printf("nb_cycle %d die %d %4d", total_cycle, all->cycle_to_die, all->nb_process);
		hexdump_map_square(all);
	}
	proc = all->stack_proc;
	while (1)
	{
		if (proc->op.opc == 1 && proc->wait == 1)
		{
			// printf("live\n");
			proc->last_live = total_cycle;
		}
		next_action(all, proc);
		if (!(proc = proc->next))
			break ;
	}
}

void		vm(t_all *all)
{
	int		total_cycle;
	t_all	*tmp_all;
	int 	cycle;
	int		i;

	cycle = 1;
	total_cycle = 0;
	init_vm(all);
	while (all->cycles_before_exit == -1 || total_cycle < all->cycles_before_exit)
	{
		make_action_and_visu(all, total_cycle++);
		if (all->flag & FLAG_CYCLE)
			printf("It is now cycle %d\n", total_cycle);
		if (cycle++ == all->cycle_to_die)
		{
			if (!check_nb_live(all, total_cycle))
				break ;
			all->nb_check++;
			if (all->nb_live >= NBR_LIVE || all->nb_check >= MAX_CHECKS)
			{
				if (all->flag & FLAG_CYCLE)
					printf("Cycle to die is now %d\n", all->cycle_to_die - CYCLE_DELTA);
				if ((all->cycle_to_die -= CYCLE_DELTA) <= 0)
				{
					if (all->flag & FLAG_CYCLE)
						printf("It is now cycle %d\n", total_cycle + 1);
					break;
				}
				all->nb_check = 0;
				all->nb_live = 0;
			}
			cycle = 1;
		}
	}
	if (all->last_player_alive)
		printf("Contestant %d, \"%s\", has won !\n", (-1) * all->last_player_alive->index, all->last_player_alive->name);
	else
		printf("Everybody lost\n");
	if (all->flag & FLAG_DUMP && total_cycle == all->cycles_before_exit)
		simple_hexdump(all);
	//while (all->flag & FLAG_VISU)
		//;
}
