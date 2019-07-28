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
	uint32_t				i;
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
					u_vm->mem_stat[tmp_proc->pc]->proc = NULL;
					u_vm->mem_stat[tmp_proc->pc]->nb_process--;
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

int run_one_cycle(int *champion_alive)
{
	t_process		*cur_proc;

	uint32_t	i;

	int y;
	int y2;
	i = 0;
	while (i < u_vm->nb_champion)
	{
		nc_print_player_status(u_vm->champions[i]);
		// mvprintw(NC_LINE_PLAYER_STATUS + (i * 8) + 5, (64 * 3) + 5, "Current pc		");
		// move(64, 65);
		// refresh();

		cur_proc = u_vm->champions[i]->processes;

			// mvprintw(50 + i, (64 * 3) + 5, "START	-1 %d      ", i);
			// move(64, 65);
			// refresh();

		if (cur_proc)
		{
			// mvprintw(NC_LINE_PLAYER_STATUS + (i * 8) + 6, (64 * 3) + 5, "									");
			// mvprintw(NC_LINE_PLAYER_STATUS + (i * 8) + 7, (64 * 3) + 5, "									");
			move(64, 65);
			refresh();
			// mvprintw(50 + i, (64 * 3) + 5, "START	0 %d      ", i);
			// move(64, 65);
			// refresh();


			y = 0;
			y2 = 0;
			(*champion_alive)++;
			while (cur_proc)
			{
			// 	mvprintw(50 + i, (64 * 3) + 5, "START	13 %d      ", i);
			// 	move(64, 65);
			// 	refresh();
				// mvprintw(NC_LINE_PLAYER_STATUS + (i * 8) + 6, (64 * 3) + 5 + y, "%d", cur_proc->pc);
				// y += 1 + ft_intlen(cur_proc->pc);

				if (cur_proc->cycle_to_run == u_vm->cycle_passed)
				{
					if (cur_proc->cur_op)
					{
					

						// mvprintw(50 + i, (64 * 3) + 5, "START	1 %s      ", cur_proc->cur_op->name);
						// move(64, 65);
						// refresh();

						cur_proc->old_pc = cur_proc->pc;
						u_vm->handlers[cur_proc->cur_op->op_code - 1](cur_proc);
							
						// mvprintw(50 + i, (64 * 3) + 5, "FINISH	1 %s    ", cur_proc->cur_op->name);
						// move(64, 65);
						// refresh();
						
						cur_proc->cycle_to_run += 1;
						cur_proc->cur_op = NULL;
					}
					else
					{
						// mvprintw(50 + i, (64 * 3) + 5, "START	22 %d    ", cur_proc->old_pc);
						// move(64, 65);
						// refresh();
						u_vm->mem_stat[cur_proc->old_pc]->proc = NULL;
						u_vm->mem_stat[cur_proc->old_pc]->nb_process--;
						nc_print(cur_proc->old_pc);
						// mvprintw(50 + i, (64 * 3) + 5, "START	23 %d    ", cur_proc->old_pc);
						// move(64, 65);
						// refresh();
						u_vm->mem_stat[cur_proc->pc]->proc = cur_proc;
						u_vm->mem_stat[cur_proc->pc]->nb_process++;
						nc_print(cur_proc->pc);
						
						cur_proc->cur_op = check_if_operation(u_vm->mem_data[cur_proc->pc]);

						if (cur_proc->cur_op)
						{
							// mvprintw(NC_LINE_PLAYER_STATUS + (i * 8) + 7, (64 * 3) + 5 + y2, "%s", cur_proc->cur_op->name);
							// y2 += 1 + ft_strlen(cur_proc->cur_op->name);
							// move(64, 65);
							// refresh();
							// mvprintw(50 + i, (64 * 3) + 5, "START	2 %s    ", cur_proc->cur_op->name);
							// move(64, 65);
							// refresh();
							cur_proc->cycle_to_run += cur_proc->cur_op->cycle;
							// mvprintw(50 + i, (64 * 3) + 5, "FINISH	2 %s    ", cur_proc->cur_op->name);
							// move(64, 65);
							// refresh();
	
						}
						else
						{
							// mvprintw(50 + i, (64 * 3) + 5, "START	3 %d    ", cur_proc->pc);
							// move(64, 65);
							// refresh();
							cur_proc->cycle_to_run += 1;

							cur_proc->old_pc = cur_proc->pc;
							
							cur_proc->pc = calc_addr(cur_proc->pc + 1);

							// mvprintw(50 + i, (64 * 3) + 5, "FINISH	3 %d     ", cur_proc->pc);
							// move(64, 65);
							// refresh();	
						}

					
					}
				}
				cur_proc = cur_proc->next;
				// mvprintw(50 + i, (64 * 3) + 5, "FINISH	13 %d      ", i);
				// move(64, 65);
				// refresh();
			}
			// mvprintw(50 + i, (64 * 3) + 5, "FINISH	0 %d    ", i);
			// move(64, 65);
			// refresh();
		}
			// mvprintw(50 + i, (64 * 3) + 5, "FINISH	-1 %d      ", i);
			// move(64, 65);
			// refresh();
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
	u_vm->paused = 0;
	u_vm->total_processes = u_vm->nb_champion;
	
	int c;

	int max_cycle_by_sec;

	max_cycle_by_sec = 1;

	while (u_vm->cycle_to_die > 0)
	{
		champion_alive = 0;
		while (u_vm->cycle_passed - u_vm->cycle_last_check < u_vm->cycle_to_die)
		{
			mvprintw(NC_LINE_CYCLE_PASSED, (64 * 3) + 5, "Cycle passed %d", u_vm->cycle_passed);
			move(64, 65);

			mvprintw(NC_LINE_SLEEP, (64 * 3) + 5, "Max cycle/sec %d", max_cycle_by_sec);
			move(64, 65);
			refresh();
			
			timeout(1);
			c = getch();

			if (c == NC_KEY_SPACE)
			{
				mvprintw(NC_LINE_POSE, (64 * 3) + 5, "paused");
				move(64, 65);
				refresh();
				u_vm->paused = 0;

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
				if (max_cycle_by_sec > 11)
					max_cycle_by_sec -= 10;
			}
			else if (c == NC_KEY_W)
			{
				if (max_cycle_by_sec > 2)
					max_cycle_by_sec -= 1;
			}
			else if (c == NC_KEY_E)
				max_cycle_by_sec += 1;
			else if (c == NC_KEY_R)
				max_cycle_by_sec += 10;
			
			run_one_cycle(&champion_alive);

			u_vm->cycle_passed++;

			// print_memory();
			// usleep(1000 * sleep_time);
			usleep((1000 * 1000) / max_cycle_by_sec);
		}
		// if (u_vm->cycle_passed > CYCLE_TO_DIE)
		// {
		// 	check_end();
		// 	if (champion_alive < 2)
		// 	{
		// 		mvprintw(2, (64 * 3) + 5, "cycle FINISHHHH --  %d", champion_alive);
		// 		move(64, 65);
		// 		refresh();

		// 		// ft_putnbr(champion_alive);
		// 		// ft_putendl(" FINISHHHH");
		// 		break;
		// 	}

		// }
		
		u_vm->cycle_last_check = u_vm->cycle_passed;
		u_vm->nbr_check++;
		if (u_vm->nbr_live > NBR_LIVE || u_vm->nbr_check == MAX_CHECKS)
		{
			u_vm->nbr_check = 0;
			u_vm->cycle_to_die -= CYCLE_DELTA;
		}
		u_vm->nbr_live = 0;
	}
	return (1);
}