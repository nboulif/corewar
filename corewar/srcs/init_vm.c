/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:59:20 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/20 17:13:18 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		init_map(t_all *all)
{
	int i;

	i = -1;
	if (!(all->map.character = malloc(sizeof(char) * MEM_SIZE)) ||
		!(all->map.color_in_map = malloc(sizeof(int) * MEM_SIZE)))
		print_error_and_exit(MALLOC_ERROR);
	ft_bzero(all->map.character, sizeof(char) * MEM_SIZE);
	while (++i < MEM_SIZE)
		all->map.color_in_map[i] = g_ncurse_color[6];
}

void		init_color_in_map(t_all *all)
{
	size_t		i;
	size_t		x;
	t_process	*proc;

	i = -1;
	while (++i < all->nb_champ)
	{
		x = -1;
		proc = &all->stack_proc[i];
		while (++x < proc->origin_champ->size_exec)
			all->map.color_in_map[x + proc->pc] =
				g_ncurse_color[proc->origin_champ->index_player];
	}
}

void		link_and_index_proc(t_all *all)
{
	int			j;
	int			i;
	t_process	*proc;

	i = -1;
	j = all->nb_champ;
	while (j)
	{
		i++;
		proc = &all->stack_proc[i];
		if (i < (int)all->nb_champ - 1)
			proc->next = &all->stack_proc[i + 1];
		else
			proc->next = NULL;
		proc->origin_champ->index_player = i;
		proc->index = j--;
		all->max++;
	}
}

void		config_stack_proc(t_all *all)
{
	size_t			i;
	t_process		*proc;

	i = -1;
	while (++i < all->nb_champ)
	{
		ft_memcpy(all->map.character + i * (MEM_SIZE / all->nb_champ),
			all->champ[i].exec_code, all->champ[i].size_exec);
		proc = &all->stack_proc[i];
		proc->origin_champ = &all->champ[i];
		proc->pc = i * (MEM_SIZE / all->nb_champ);
		proc->carry = 0;
		proc->reg[0] = all->champ[i].index;
	}
}

void		init_vm(t_all *all)
{
	init_map(all);
	if (!(all->stack_proc = malloc(all->nb_champ * sizeof(t_process))))
		print_error_and_exit(MALLOC_ERROR);
	ft_bzero(all->map.character, MEM_SIZE);
	ft_bzero(all->stack_proc, all->nb_champ * sizeof(t_process));
	config_stack_proc(all);
	link_and_index_proc(all);
	all->nb_process = all->nb_champ;
	if (all->flag & FLAG_VISU)
		init_color_in_map(all);
}
