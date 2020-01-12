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

char paused = 0;
char jump = 0;




void		hexdump_map_square(t_all *all)
{
	int		proc;
	int		i;
	char	*last_color;

	if (!(all->flag & FLAG_VISU))
		return ;
	i = -1;
	last_color = NULL;

	int old_color = 0;

	while (++i < MEM_SIZE)
	{
		proc = is_a_process(all, i);

		if (proc)
		{
			if (old_color != 69 + g_ncurse_color[proc])
			{
				if (old_color)
					attroff(COLOR_PAIR(old_color));
				attron(COLOR_PAIR(69 + g_ncurse_color[proc]));
				old_color = 69 + g_ncurse_color[proc];
			}
			mvprintw(i / 64, (i % 64) * 3, "%.2hhx", all->map.character[i]);
		}
		else
		{

			if (old_color != 100 + all->map.color_in_map[i])
			{
				if (old_color)
					attroff(COLOR_PAIR(old_color));
				attron(COLOR_PAIR(100 + all->map.color_in_map[i]));
				old_color = 100 + all->map.color_in_map[i];
			}
			mvprintw(i / 64, (i % 64) * 3, "%.2hhx", all->map.character[i]);
		}

	}

}
