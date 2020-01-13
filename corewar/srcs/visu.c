/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:15:35 by nsondag           #+#    #+#             */
/*   Updated: 2020/01/11 19:18:39 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		simple_hexdump(t_all *all, int bytes_per_line)
{
	int	octet;

	octet = 0;
	ft_printf("0x%04x : ", octet);
	while (octet < MEM_SIZE)
	{
		ft_printf("%.2hhx ", all->map.character[octet]);
		if (octet && !((octet + 1) % bytes_per_line) && octet + 1 < MEM_SIZE)
		{
			ft_printf("\n");
			ft_printf("0x%04x : ", octet + 1);
		}
		octet++;
	}
	ft_printf("\n");
}

void		ncurses_print_map_square(t_all *all)
{
	int		proc;
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		proc = is_a_process(all, i);
		if (proc)
		{
			attron(COLOR_PAIR(69 + g_ncurse_color[proc]));
			mvprintw(i / 64, (i % 64) * 3, "%.2hhx", all->map.character[i]);
			attroff(COLOR_PAIR(69 + g_ncurse_color[proc]));
		}
		else
		{
			attron(COLOR_PAIR(100 + all->map.color_in_map[i]));
			mvprintw(i / 64, (i % 64) * 3, "%.2hhx", all->map.character[i]);
			attroff(COLOR_PAIR(100 + all->map.color_in_map[i]));
		}
	}
}

void		ncurses_print_screen(t_all *all)
{
	ncurses_print_info(all);
	ncurses_print_player_info(all);
	ncurses_print_map_square(all);
	refresh();
	ncurses_event_handler(all);
	usleep((1000 * 1000) / all->max_cycle_by_sec);
}

void		init_ncurses(void)
{
	initscr();
	curs_set(FALSE);
	start_color();
	init_pair(100, 0, 0);
	init_pair(101, 1, 0);
	init_pair(102, 2, 0);
	init_pair(103, 3, 0);
	init_pair(104, 4, 0);
	init_pair(107, 7, 0);
	init_pair(71, 7, 1);
	init_pair(72, 7, 2);
	init_pair(73, 7, 3);
	init_pair(74, 7, 4);
	init_pair(77, 7, 7);
	attron(A_BOLD);
	mvprintw(NC_LINE_PAUSED, (64 * 3) + 5, "** PAUSED **");
}
