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

void	ncurses_print_info(t_all *all, int total_cycle)
{
	attron(COLOR_PAIR(107));
	mvprintw(NC_LINE_CYCLE_PASSED, 64 * 3 + 20,
		"max cycle by sec %4d", all->max_cycle_by_sec);
	mvprintw(NC_LINE_CYCLE_PASSED + 1, 64 * 3 + 20,
		"nb_cycle %d", total_cycle);
	mvprintw(NC_LINE_CYCLE_PASSED + 2, 64 * 3 + 20,
		"die %d", all->cycle_to_die);
	mvprintw(NC_LINE_CYCLE_PASSED + 3, 64 * 3 + 20,
		"nb_process %d", all->nb_process);
	attroff(COLOR_PAIR(107));
}

void	ncurses_manage_pause(t_all *all)
{
	if (all->nc_paused)
	{
		mvprintw(NC_LINE_POSE, (64 * 3) + 5, "      ");
		all->nc_paused = 0;
	}
	else
	{
		mvprintw(NC_LINE_POSE, (64 * 3) + 5, "paused");
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

void	ncurses_event_handler(t_all *all, int total_cycle)
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
			ncurses_print_info(all, total_cycle);
		if (!all->nc_paused)
			break ;
		usleep(500);
		c = '\0';
	}
}
