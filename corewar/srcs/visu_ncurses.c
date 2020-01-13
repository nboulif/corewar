/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_ncurses.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:15:35 by nsondag           #+#    #+#             */
/*   Updated: 2020/01/11 19:18:39 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void	ncurses_print_player_info(t_all *all)
{
	size_t i;

	i = -1;
	while (++i < all->nb_champ)
	{
		mvprintw(NC_LINE_PLAYER_STATUS + 0 + (5 * i), 64 * 3 + 5,
			"Player %3d : ", all->champ[i].index);
		attron(COLOR_PAIR(100 + g_ncurse_color[all->champ[i].index_player]));
		mvprintw(NC_LINE_PLAYER_STATUS + 0 + (5 * i), 64 * 3 + 5 + 13,
			"%s", all->champ[i].name);
		attroff(COLOR_PAIR(100 + g_ncurse_color[all->champ[i].index_player]));
		mvprintw(NC_LINE_PLAYER_STATUS + 1 + (5 * i), 64 * 3 + 5,
			"last live %d", all->champ[i].last_live);
		mvprintw(NC_LINE_PLAYER_STATUS + 2 + (5 * i), 64 * 3 + 5,
			"nb live curr periode %d", all->champ[i].nb_live_cur_period);
	}
}

void	ncurses_print_info(t_all *all)
{
	mvprintw(NC_LINE_MAX_CYCLE, 64 * 3 + 5,
		"Cycles/second limit : %-10d", all->max_cycle_by_sec);
	mvprintw(NC_LINE_CYCLE_PASSED, 64 * 3 + 5,
		"Cycle : %-10d", all->total_cycle);
	mvprintw(NC_LINE_PROC_PASSED, 64 * 3 + 5,
		"Processes : %-10d", all->nb_process);
	mvprintw(NC_LINE_CYCLE_TO_DIE, 64 * 3 + 5,
		"CYCLE_TO_DIE : %-10d", all->cycle_to_die);
	mvprintw(NC_LINE_CYCLE_TO_DIE + 2, 64 * 3 + 5,
		"CYCLE_DELTA : %-10d", CYCLE_DELTA);
	mvprintw(NC_LINE_CYCLE_TO_DIE + 4, 64 * 3 + 5,
		"NBR_LIVE : %-10d", NBR_LIVE);
	mvprintw(NC_LINE_CYCLE_TO_DIE + 6, 64 * 3 + 5,
		"MAX_CHECKS : %-10d", MAX_CHECKS);
}

void	ncurses_manage_pause(t_all *all)
{
	if (all->nc_paused)
	{
		mvprintw(NC_LINE_PAUSED, (64 * 3) + 5, "            ");
		all->nc_paused = 0;
	}
	else
	{
		mvprintw(NC_LINE_PAUSED, (64 * 3) + 5, "** PAUSED **");
		all->nc_paused = 1;
	}
	refresh();
}

void	ncurses_manage_max_speed(t_all *all, char c)
{
	if (c == NC_KEY_Q)
	{
		if (all->max_cycle_by_sec > 11)
			all->max_cycle_by_sec -= 10;
	}
	else if (c == NC_KEY_W)
	{
		if (all->max_cycle_by_sec > 2)
			all->max_cycle_by_sec -= 1;
	}
	else if (c == NC_KEY_E)
		all->max_cycle_by_sec += 1;
	else if (c == NC_KEY_R)
		all->max_cycle_by_sec += 10;
}

void	ncurses_event_handler(t_all *all)
{
	char	c;

	while (1)
	{
		c = getch();
		timeout(1);
		if (c == NC_KEY_SPACE)
			ncurses_manage_pause(all);
		else if (c == NC_KEY_ENTER && all->nc_paused)
			break ;
		else
			ncurses_manage_max_speed(all, c);
		if (c)
			ncurses_print_info(all);
		if (!all->nc_paused)
			break ;
		usleep(500);
		c = '\0';
	}
}
