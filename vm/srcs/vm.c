/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		init_champions(void)
{
	int id;

	id = 0;
	while (id < (int)u_vm->nb_champion)
	{
		id + 1 == 1 ? u_vm->champions[id]->color = ft_strdup(PF_COLOR_PLAYER_1) : 0;
		id + 1 == 1 ? u_vm->champions[id]->nc_color = NC_COLOR_PLAYER_1 : 0;
		id + 1 == 2 ? u_vm->champions[id]->color = ft_strdup(PF_COLOR_PLAYER_2) : 0;
		id + 1 == 2 ? u_vm->champions[id]->nc_color = NC_COLOR_PLAYER_2 : 0;
		id + 1 == 3 ? u_vm->champions[id]->color = ft_strdup(PF_COLOR_PLAYER_3) : 0;
		id + 1 == 3 ? u_vm->champions[id]->nc_color = NC_COLOR_PLAYER_3 : 0;
		id + 1 == 4 ? u_vm->champions[id]->color = ft_strdup(PF_COLOR_PLAYER_4) : 0;
		id + 1 == 4 ? u_vm->champions[id]->nc_color = NC_COLOR_PLAYER_4 : 0;

		u_vm->champions[id]->id = -(id + 1);
		u_vm->champions[id]->last_live = 0;
		u_vm->champions[id]->total_lives = 0;

		u_vm->champions[id]->processes = (t_process*)malloc(sizeof(t_process));
		u_vm->champions[id]->nb_processes = 1;
		
		uint32_t i;
		
		i = 0;
		while (i < REG_NUMBER)
			u_vm->champions[id]->processes->regs[i++] = (uint32_t)0;

		u_vm->champions[id]->processes->regs[0] = u_vm->champions[id]->id;
		u_vm->champions[id]->processes->pc = id * (MEM_SIZE / u_vm->nb_champion);
		u_vm->champions[id]->processes->old_pc = u_vm->champions[id]->processes->pc;
		u_vm->champions[id]->processes->carry = 0;

		u_vm->champions[id]->processes->cycle_to_run = 0;
		u_vm->champions[id]->processes->nbr_live = 0;
		u_vm->champions[id]->processes->cur_op = NULL;

		u_vm->champions[id]->processes->champion = u_vm->champions[id];

		u_vm->champions[id]->processes->prev = NULL;
		u_vm->champions[id]->processes->next = NULL;
		

		i = 0;
		while (i < u_vm->champions[id]->prog->prog_size)
		{
			u_vm->mem_data[u_vm->champions[id]->processes->pc + i] = 
				u_vm->champions[id]->prog->prog[i];
			u_vm->mem_stat[u_vm->champions[id]->processes->pc + i]->nc_color = u_vm->champions[id]->nc_color;
			u_vm->mem_stat[u_vm->champions[id]->processes->pc + i]->color = u_vm->champions[id]->color;
			nc_print(u_vm->champions[id]->processes->pc + i);
			i++;
		}
		id++;
	}
	return (1);
}

int		main(int argc, char *argv[])
{	
	if (argc < 2)
	{
		ft_putendl("WRONG NB PARAM");
		return (0);
	}

	u_vm = (t_vm*)malloc(sizeof(t_vm));
	init_handlers();
	parse_champions(argc, argv);
	
	initscr();
	start_color();
	
	init_pairs();

	int i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		u_vm->mem_data[i] = 0;

		u_vm->mem_stat[i]->proc = NULL;
		u_vm->mem_stat[i]->nb_process = 0;

		u_vm->mem_stat[i]->color = PF_COLOR_WHITE;
		u_vm->mem_stat[i]->nc_color = NC_COLOR_WHITE;
		nc_print(i);
	}

	init_champions();

	start_battle();
	timeout(-1);
    getch();
    endwin();
	return (0);
}
