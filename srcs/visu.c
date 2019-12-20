/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:15:35 by nsondag           #+#    #+#             */
/*   Updated: 2019/12/20 16:24:46 by nsondag          ###   ########.fr       */
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

void		hexdump_map_square(t_all *all)
{
	int		proc;
	int		i;
	char	*last_color;

	if (!(all->flag & FLAG_VISU))
		return ;
	i = -1;
	last_color = NULL;
	move_to(0, 0);
	while (++i < MEM_SIZE)
	{
		proc = is_a_process(all, i);
		if (proc)
		{
			if (last_color != background_color[proc])
				printf("%s", (last_color = background_color[proc]));
		}
		else if (last_color != all->map.color_in_map[i])
			printf("%s", (last_color = all->map.color_in_map[i]));
		if (!((i + 1) % 64))
			printf("%.2hhx\n", all->map.character[i]);
		else
			printf("%.2hhx\033[0;39m %s", all->map.character[i], last_color);
	}
	read(0, &i, 4);
}
