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
pthread_mutex_t mutex;

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
			if (last_color != g_background_color[proc])
				ft_printf("%s", (last_color = g_background_color[proc]));
		}
		else if (last_color != all->map.color_in_map[i])
			ft_printf("%s", (last_color = all->map.color_in_map[i]));
		if (!((i + 1) % 64))
			ft_printf("%.2hhx\n", all->map.character[i]);
		else
			ft_printf("%.2hhx\033[0;39m %s", all->map.character[i], last_color);
	}

	// pthread_mutex_lock(&mutex);
	// while (1)
	// {
	// 	if (!paused)
	// 		break ;
	// 	if (jump)
	// 	{
	// 		jump--;
	// 		break ;
	// 	}
	// 	usleep(50000);
	// }
	// pthread_mutex_unlock(&mutex);
}

// int 	read_command()
// {
// 	char	line;
// 	int		ret;

// 	line = getchar_unlocked();
// 	if (line == ' ')
// 		ret = PAUSE;
// 	else if (line == 's')
// 		ret = ONE_JUMP;
// 	else 
// 		ret = 0;
// 	return (ret);
// }

// void	*check_pause(void *arg)
// {
// 	char rep;

// 	(void)arg;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		if ((rep = read_command()) == PAUSE)
// 			paused = 1 - paused;
// 		else if (rep == ONE_JUMP)
// 			jump++;
// 		pthread_mutex_unlock(&mutex);
// 	}
//     pthread_exit(NULL);
// }