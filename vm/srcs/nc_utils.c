/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int nc_print_mem(uint32_t index, int fg_color, int bg_color)
{
	attron((COLOR_PAIR((fg_color == NC_COLOR_BLACK ? 100 : fg_color * 10) + bg_color)));
	mvprintw(index / 64, (index % 64) * 3, "%.2x", u_vm->mem_data[index]);
	attroff((COLOR_PAIR((fg_color == NC_COLOR_BLACK ? 100 : fg_color * 10) + bg_color)));
	mvprintw(index / 64, ((index % 64) * 3) + 2, " ");
	move(64, 65);
	refresh();
	return (1);
}

int nc_print_line(int x, int y, int paired_color, char *str)
{
	attron(COLOR_PAIR(paired_color));
	mvprintw(y, x, "%s",str);
	attroff(COLOR_PAIR(paired_color));
	move(64, 65);
	refresh();
	return (1);
}

int nc_print_player_status(t_champion *champ)
{
	mvprintw(NC_LINE_PLAYER_STATUS + ((-(champ->id) - 1) * 8) + 0, (64 * 3) + 5,
		"Player			%d", (champ->id));
	mvprintw(NC_LINE_PLAYER_STATUS + ((-(champ->id) - 1) * 8) + 1, (64 * 3) + 5,
		"Processes		%d", champ->nb_processes);
	mvprintw(NC_LINE_PLAYER_STATUS + ((-(champ->id) - 1) * 8) + 2, (64 * 3) + 5,
		"Last Live		%d", champ->last_live);
	mvprintw(NC_LINE_PLAYER_STATUS + ((-(champ->id) - 1) * 8) + 3, (64 * 3) + 5,
		"Total Lives	%d", champ->total_lives);
	move(64, 65);
	refresh();
	return (1);
}

int nc_print(uint32_t index)
{	
	if (u_vm->mem_stat[index]->proc)
		nc_print_mem(index, NC_COLOR_BLACK, u_vm->mem_stat[index]->proc->champion->nc_color);
	else
		nc_print_mem(index, u_vm->mem_stat[index]->nc_color, NC_COLOR_BLACK);

	// if (u_vm->mem_stat[index]->proc)
	// {
	// 	// if (u_vm->mem_data[index]->nb_process == 1)
	// 		attroff(COLOR_PAIR((NC_COLOR_BLACK * 10) + u_vm->mem_stat[index]->proc->champion->nc_color));
	// 	// else
	// 		// attroff(COLOR_PAIR((u_vm->mem_data[index]->nc_color * 10) + u_vm->mem_data[index]->nc_color));
	// }
	// else
	// 	attroff(COLOR_PAIR((u_vm->mem_stat[index]->nc_color * 10) + NC_COLOR_BLACK));
	
	// mvprintw(index / 64, ((index % 64) * 3) + 2, " ");

	// move(64, 65);
	// refresh();

	return (1);
}

void			init_pairs(void)
{
	init_pair(NC_COLOR_BLACK , NC_COLOR_BLACK , NC_COLOR_WHITE);
	init_pair(NC_COLOR_RED , NC_COLOR_RED , NC_COLOR_BLACK);
	init_pair(NC_COLOR_GREEN , NC_COLOR_GREEN , NC_COLOR_BLACK);
	init_pair(NC_COLOR_YELLOW , NC_COLOR_YELLOW , NC_COLOR_BLACK);
	init_pair(NC_COLOR_BLUE , NC_COLOR_BLUE , NC_COLOR_BLACK);
	init_pair(NC_COLOR_MAGENTA , NC_COLOR_MAGENTA , NC_COLOR_BLACK);
	init_pair(NC_COLOR_CYAN , NC_COLOR_CYAN , NC_COLOR_BLACK);
	init_pair(NC_COLOR_WHITE , NC_COLOR_WHITE , NC_COLOR_BLACK);

	init_pair((NC_COLOR_PLAYER_1 * 10) + NC_COLOR_BLACK, NC_COLOR_PLAYER_1, NC_COLOR_BLACK);
	init_pair((NC_COLOR_PLAYER_1 * 10) + NC_COLOR_WHITE, NC_COLOR_PLAYER_1, NC_COLOR_WHITE);
	init_pair((NC_COLOR_PLAYER_1 * 10) + NC_COLOR_PLAYER_1, NC_COLOR_PLAYER_1, NC_COLOR_PLAYER_1);
	init_pair((NC_COLOR_PLAYER_1 * 10) + NC_COLOR_PLAYER_2, NC_COLOR_PLAYER_1, NC_COLOR_PLAYER_2);
	init_pair((NC_COLOR_PLAYER_1 * 10) + NC_COLOR_PLAYER_3, NC_COLOR_PLAYER_1, NC_COLOR_PLAYER_3);
	init_pair((NC_COLOR_PLAYER_1 * 10) + NC_COLOR_PLAYER_4, NC_COLOR_PLAYER_1, NC_COLOR_PLAYER_4);

	init_pair((NC_COLOR_PLAYER_2 * 10) + NC_COLOR_BLACK, NC_COLOR_PLAYER_2, NC_COLOR_BLACK);
	init_pair((NC_COLOR_PLAYER_2 * 10) + NC_COLOR_WHITE, NC_COLOR_PLAYER_2, NC_COLOR_WHITE);
	init_pair((NC_COLOR_PLAYER_2 * 10) + NC_COLOR_PLAYER_2, NC_COLOR_PLAYER_2, NC_COLOR_PLAYER_2);
	init_pair((NC_COLOR_PLAYER_2 * 10) + NC_COLOR_PLAYER_1, NC_COLOR_PLAYER_2, NC_COLOR_PLAYER_1);
	init_pair((NC_COLOR_PLAYER_2 * 10) + NC_COLOR_PLAYER_3, NC_COLOR_PLAYER_2, NC_COLOR_PLAYER_3);
	init_pair((NC_COLOR_PLAYER_2 * 10) + NC_COLOR_PLAYER_4, NC_COLOR_PLAYER_2, NC_COLOR_PLAYER_4);

	init_pair((NC_COLOR_PLAYER_3 * 10) + NC_COLOR_BLACK, NC_COLOR_PLAYER_3, NC_COLOR_BLACK);
	init_pair((NC_COLOR_PLAYER_3 * 10) + NC_COLOR_WHITE, NC_COLOR_PLAYER_3, NC_COLOR_WHITE);
	init_pair((NC_COLOR_PLAYER_3 * 10) + NC_COLOR_PLAYER_3, NC_COLOR_PLAYER_3, NC_COLOR_PLAYER_3);
	init_pair((NC_COLOR_PLAYER_3 * 10) + NC_COLOR_PLAYER_2, NC_COLOR_PLAYER_3, NC_COLOR_PLAYER_2);
	init_pair((NC_COLOR_PLAYER_3 * 10) + NC_COLOR_PLAYER_1, NC_COLOR_PLAYER_3, NC_COLOR_PLAYER_1);
	init_pair((NC_COLOR_PLAYER_3 * 10) + NC_COLOR_PLAYER_4, NC_COLOR_PLAYER_3, NC_COLOR_PLAYER_4);

	init_pair((NC_COLOR_PLAYER_4 * 10) + NC_COLOR_BLACK, NC_COLOR_PLAYER_4, NC_COLOR_BLACK);
	init_pair((NC_COLOR_PLAYER_4 * 10) + NC_COLOR_WHITE, NC_COLOR_PLAYER_4, NC_COLOR_WHITE);
	init_pair((NC_COLOR_PLAYER_4 * 10) + NC_COLOR_PLAYER_4, NC_COLOR_PLAYER_4, NC_COLOR_PLAYER_4);
	init_pair((NC_COLOR_PLAYER_4 * 10) + NC_COLOR_PLAYER_2, NC_COLOR_PLAYER_4, NC_COLOR_PLAYER_2);
	init_pair((NC_COLOR_PLAYER_4 * 10) + NC_COLOR_PLAYER_3, NC_COLOR_PLAYER_4, NC_COLOR_PLAYER_3);
	init_pair((NC_COLOR_PLAYER_4 * 10) + NC_COLOR_PLAYER_1, NC_COLOR_PLAYER_4, NC_COLOR_PLAYER_1);

	init_pair((NC_COLOR_WHITE * 10) + NC_COLOR_BLACK, NC_COLOR_WHITE, NC_COLOR_BLACK);
	init_pair((NC_COLOR_WHITE * 10) + NC_COLOR_WHITE, NC_COLOR_WHITE, NC_COLOR_WHITE);
	init_pair((NC_COLOR_WHITE * 10) + NC_COLOR_PLAYER_1, NC_COLOR_WHITE, NC_COLOR_PLAYER_1);
	init_pair((NC_COLOR_WHITE * 10) + NC_COLOR_PLAYER_2, NC_COLOR_WHITE, NC_COLOR_PLAYER_2);
	init_pair((NC_COLOR_WHITE * 10) + NC_COLOR_PLAYER_3, NC_COLOR_WHITE, NC_COLOR_PLAYER_3);
	init_pair((NC_COLOR_WHITE * 10) + NC_COLOR_PLAYER_4, NC_COLOR_WHITE, NC_COLOR_PLAYER_4);
	
	init_pair(100 + NC_COLOR_BLACK, NC_COLOR_BLACK, NC_COLOR_BLACK);
	init_pair(100 + NC_COLOR_WHITE, NC_COLOR_BLACK, NC_COLOR_WHITE);
	init_pair(100 + NC_COLOR_PLAYER_1, NC_COLOR_BLACK, NC_COLOR_PLAYER_1);
	init_pair(100 + NC_COLOR_PLAYER_2, NC_COLOR_BLACK, NC_COLOR_PLAYER_2);
	init_pair(100 + NC_COLOR_PLAYER_3, NC_COLOR_BLACK, NC_COLOR_PLAYER_3);
	init_pair(100 + NC_COLOR_PLAYER_4, NC_COLOR_BLACK, NC_COLOR_PLAYER_4);
	
}
