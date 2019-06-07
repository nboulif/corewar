/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int check_end(void)
{
	unsigned int	i;
	t_process		*cur_proc;

	i = 0;
	while (i < u_vm->nb_champion)
	{
		cur_proc = u_vm->champions[i]->processes;
		while (cur_proc)
		{
			if (!cur_proc->nbr_live)
			{
				t_process		*tmp_proc;

				tmp_proc = cur_proc;
				while (tmp_proc && !tmp_proc->nbr_live)
				{
					u_vm->memory[tmp_proc->pc]->proc = NULL;
					u_vm->memory[tmp_proc->pc]->nb_process--;
					tmp_proc = tmp_proc->next;
				}
				if (tmp_proc)
				{
					if (cur_proc->prev)
					{
						cur_proc->prev->next = tmp_proc;
						tmp_proc->prev = cur_proc->prev;
					}
					else
					{
						u_vm->champions[i]->processes = tmp_proc;
						tmp_proc->prev = NULL;
					}
					cur_proc = tmp_proc;

					cur_proc->nbr_live = 0;
					cur_proc = cur_proc->next;
				}
				else
				{
					cur_proc = NULL;
					u_vm->champions[i]->processes = NULL;
				}
			}
			else
			{
				cur_proc->nbr_live = 0;
				cur_proc = cur_proc->next;
			}
		}
		i++;
	}
	return (1);
}

int nc_print(unsigned int index)
{	
	
	if (u_vm->memory[index]->proc)
	{
		if (u_vm->memory[index]->nb_process == 1)
			attron(COLOR_PAIR((NC_COLOR_WHITE * 10) + u_vm->memory[index]->proc->champion->nc_color));
		else
			attron(COLOR_PAIR((u_vm->memory[index]->nc_color * 10) + u_vm->memory[index]->nc_color));
	}
	else
		attron((COLOR_PAIR(u_vm->memory[index]->nc_color * 10) + NC_COLOR_BLACK));

	mvprintw(index / 64, (index % 64) * 3, "%.2x", u_vm->memory[index]->data);

	if (u_vm->memory[index]->proc)
	{
		if (u_vm->memory[index]->nb_process == 1)
			attroff(COLOR_PAIR((NC_COLOR_WHITE * 10) + u_vm->memory[index]->proc->champion->nc_color));
		else
			attroff(COLOR_PAIR((u_vm->memory[index]->nc_color * 10) + u_vm->memory[index]->nc_color));
	}
	else
		attroff(COLOR_PAIR((u_vm->memory[index]->nc_color * 10) + NC_COLOR_BLACK));
	
	mvprintw(index / 64, ((index % 64) * 3) + 2, " ", u_vm->memory[index]->data);

	move(64, 65);
	refresh();

	return (1);
}

int run_one_cycle(int *champion_alive)
{
	t_process		*cur_proc;

	unsigned int	i;

	i = 0;
	while (i < u_vm->nb_champion)
	{

		mvprintw(NC_LINE_PLAYER_STATUS + (i * 7) + 0, (64 * 3) + 5, "Player			%d", u_vm->champions[i]->id);
		mvprintw(NC_LINE_PLAYER_STATUS + (i * 7) + 1, (64 * 3) + 5, "Processes		%d", u_vm->champions[i]->nb_processes);
		mvprintw(NC_LINE_PLAYER_STATUS + (i * 7) + 2, (64 * 3) + 5, "Last Live		%d", u_vm->champions[i]->last_live);
		mvprintw(NC_LINE_PLAYER_STATUS + (i * 7) + 3, (64 * 3) + 5, "Total Lives	%d", u_vm->champions[i]->total_lives);
		mvprintw(NC_LINE_PLAYER_STATUS + (i * 7) + 4, (64 * 3) + 5, "Current pc		");
		move(64, 65);
		refresh();

		cur_proc = u_vm->champions[i]->processes;

		if (cur_proc)
		{
			mvprintw(NC_LINE_PLAYER_STATUS + (i * 7) + 5, (64 * 3) + 5, "							");
			refresh();
		
			int y;

			y = 0;
			(*champion_alive)++;
			while (cur_proc)
			{
				mvprintw(NC_LINE_PLAYER_STATUS + (i * 7) + 5, (64 * 3) + 5 + y, "%d", cur_proc->pc);
				y += 1 + ft_intlen(cur_proc->pc);

				move(64, 65);
				refresh();
				if (cur_proc->cycle_to_run == u_vm->cycle_passed)
				{
					if (cur_proc->cur_op)
					{
						mvprintw(50, (64 * 3) + 5, "START	1 %s      ", cur_proc->cur_op->name);
						move(64, 65);
						refresh();

						cur_proc->old_pc = cur_proc->pc;
						
						u_vm->handlers[cur_proc->cur_op->op_code - 1](cur_proc);
						
						cur_proc->pc = (cur_proc->pc % MEM_SIZE);
	
	
						mvprintw(50, (64 * 3) + 5, "FINISH	1 %s    ", cur_proc->cur_op->name);
						move(64, 65);
						refresh();
						
						cur_proc->cycle_to_run += 1;
						cur_proc->cur_op = NULL;
					}
					else
					{
						u_vm->memory[cur_proc->old_pc]->proc = NULL;
						u_vm->memory[cur_proc->old_pc]->nb_process--;
						nc_print(cur_proc->old_pc);

						cur_proc->old_pc = cur_proc->pc;

						u_vm->memory[cur_proc->pc]->proc = cur_proc;
						u_vm->memory[cur_proc->pc]->nb_process++;
						nc_print(cur_proc->pc);
						
						cur_proc->cur_op = check_if_operation(u_vm->memory[cur_proc->pc]->data);

						if (cur_proc->cur_op)
						{

							mvprintw(50, (64 * 3) + 5, "START	2 %s    ", cur_proc->cur_op->name);
							move(64, 65);
							refresh();
							cur_proc->cycle_to_run += cur_proc->cur_op->cycle;
							mvprintw(50, (64 * 3) + 5, "FINISH	2 %s    ", cur_proc->cur_op->name);
							move(64, 65);
							refresh();
	
						}
						else
						{
							mvprintw(50, (64 * 3) + 5, "START	3 %d     ", cur_proc->pc);
							move(64, 65);
							refresh();


							nc_print(cur_proc->pc);
							
							cur_proc->cycle_to_run += 1;
							cur_proc->pc = ((cur_proc->pc + 1) % MEM_SIZE);

							mvprintw(50, (64 * 3) + 5, "FINISH	3 %d     ", cur_proc->pc);
							move(64, 65);
							refresh();	
						}

					
					}
				}
				cur_proc = cur_proc->next;
			}
			
		}
		i++;
	}
	return (1);
}

int start_battle(void)
{
	int				champion_alive;

	u_vm->cycle_to_die = CYCLE_TO_DIE;
	u_vm->cycle_passed = 0;
	u_vm->cycle_last_check = 0;
	u_vm->nbr_check = 0;
	u_vm->nbr_live = 0;
	u_vm->total_processes = u_vm->nb_champion;
	
	int c;

	int sleep_time;

	sleep_time = 500;

	while (u_vm->cycle_to_die > 0)
	{
		champion_alive = 0;
		while (u_vm->cycle_passed - u_vm->cycle_last_check < u_vm->cycle_to_die)
		{
			mvprintw(NC_LINE_CYCLE_PASSED, (64 * 3) + 5, "cycle passed %d", u_vm->cycle_passed);
			move(64, 65);

			mvprintw(NC_LINE_SLEEP, (64 * 3) + 5, "sleep time %d", sleep_time);
			move(64, 65);
			refresh();
			
			timeout(1);
			c = getch();

			if (c == NC_KEY_SPACE)
			{
				mvprintw(NC_LINE_POSE, (64 * 3) + 5, "paused");
				move(64, 65);
				refresh();

				c = '\0';
				while (c != NC_KEY_SPACE)
				{
					timeout(1);
					c = getch();
				}

				mvprintw(NC_LINE_POSE, (64 * 3) + 5, "      ");
				move(64, 65);
				refresh();
			}
			else if (c == NC_KEY_Q)
			{
				if (sleep_time < 1000)
				{
					sleep_time += 100;
				}
			}
			else if (c == NC_KEY_W)
			{
				if (sleep_time < 1000)
				{
					sleep_time += 10;
				}
			}
			else if (c == NC_KEY_E)
			{
				if (sleep_time > 0)
				{
					sleep_time -= 10;
				}
			}
			else if (c == NC_KEY_R)
			{
				if (sleep_time > 0)
				{
					sleep_time -= 100;
				}
			}
			
			
			run_one_cycle(&champion_alive);

			u_vm->cycle_passed++;

			// print_memory();
			usleep(1000 * sleep_time);
		}

		check_end();

		if (champion_alive < 2)
		{
	
			mvprintw(2, (64 * 3) + 5, "cycle FINISHHHH --  %d", champion_alive);
			move(64, 65);
			refresh();

			// ft_putnbr(champion_alive);
			// ft_putendl(" FINISHHHH");
			break;
		}

		u_vm->cycle_last_check = u_vm->cycle_passed;
		u_vm->nbr_check++;
		if (u_vm->nbr_live > NBR_LIVE)
			u_vm->cycle_to_die -= CYCLE_DELTA;
		u_vm->nbr_live = 0;
	}
	return (1);
}