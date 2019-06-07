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

t_op 	*check_if_operation(unsigned char octet)
{
	int i;

	i = -1;
	while (++i < 16)
		if (g_op_tab[i].op_code == octet)
			return (&g_op_tab[i]);
	return (NULL);
	
}

void	print_memory(void)
{
	int i;
	int y;

	i = 0;
	while (i < MEM_SIZE)
	{
		y = -1;
		while (++y < 64)
		{
			printf("%s", u_vm->memory[i]->color);
			printf("%.2x ", u_vm->memory[i]->data);
			printf(PF_COLOR_RESET);

			i++;
		}

		printf("\n");
	}
	printf("\n");

}

int		init_champions(void)
{
	unsigned int id;

	id = 0;
	while (id < u_vm->nb_champion)
	{
		id + 1 == 1 ? u_vm->champions[id]->color = ft_strdup(PF_COLOR_PLAYER_1) : 0;
		id + 1 == 1 ? u_vm->champions[id]->nc_color = NC_COLOR_PLAYER_1 : 0;
		id + 1 == 2 ? u_vm->champions[id]->color = ft_strdup(PF_COLOR_PLAYER_2) : 0;
		id + 1 == 2 ? u_vm->champions[id]->nc_color = NC_COLOR_PLAYER_2 : 0;
		id + 1 == 3 ? u_vm->champions[id]->color = ft_strdup(PF_COLOR_PLAYER_3) : 0;
		id + 1 == 3 ? u_vm->champions[id]->nc_color = NC_COLOR_PLAYER_3 : 0;
		id + 1 == 4 ? u_vm->champions[id]->color = ft_strdup(PF_COLOR_PLAYER_4) : 0;
		id + 1 == 4 ? u_vm->champions[id]->nc_color = NC_COLOR_PLAYER_4 : 0;

		u_vm->champions[id]->id = id + 1;
		u_vm->champions[id]->last_live = 0;
		u_vm->champions[id]->total_lives = 0;

		u_vm->champions[id]->processes = (t_process*)malloc(sizeof(t_process));
		u_vm->champions[id]->nb_processes = 1;
		
		unsigned int i;
		
		i = 0;
		while (i < REG_NUMBER)
			u_vm->champions[id]->processes->regs[i++] = (unsigned int)0;

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
			u_vm->memory[u_vm->champions[id]->processes->pc + i]->data = 
				u_vm->champions[id]->prog->prog[i];
			u_vm->memory[u_vm->champions[id]->processes->pc + i]->nc_color = u_vm->champions[id]->nc_color;
			u_vm->memory[u_vm->champions[id]->processes->pc + i]->color = u_vm->champions[id]->color;
			nc_print(u_vm->champions[id]->processes->pc + i);
			i++;
		}
		id++;
	}
	return (1);
}

void			init_handlers(void)
{
	u_vm->handlers[0] = &handle_label_live;
	u_vm->handlers[1] = &handle_label_ld;
	u_vm->handlers[2] = &handle_label_st;
	u_vm->handlers[3] = &handle_label_add;
	u_vm->handlers[4] = &handle_label_sub;
	u_vm->handlers[5] = &handle_label_and;
	u_vm->handlers[6] = &handle_label_or;
	u_vm->handlers[7] = &handle_label_xor;
	u_vm->handlers[8] = &handle_label_zjmp;
	u_vm->handlers[9] = &handle_label_ldi;
	u_vm->handlers[10] = &handle_label_sti;
	u_vm->handlers[11] = &handle_label_fork;
	u_vm->handlers[12] = &handle_label_lld;
	u_vm->handlers[13] = &handle_label_lldi;
	u_vm->handlers[14] = &handle_label_lfork;
	u_vm->handlers[15] = &handle_label_aff;
}
void			init_pairs(void)
{
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
		u_vm->memory[i]->data = 0;
		u_vm->memory[i]->proc = NULL;
		u_vm->memory[i]->nb_process = 0;

		u_vm->memory[i]->color = PF_COLOR_WHITE;
		u_vm->memory[i]->nc_color = NC_COLOR_WHITE;
		nc_print(i);
	}

	init_champions();

	start_battle();
	timeout(-1);
    getch();
    endwin();
	return (0);
}
