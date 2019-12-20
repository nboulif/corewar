/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_visu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 14:01:03 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/20 16:46:17 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		change_color(t_all *all, t_process *proc, int i)
{
	all->map.color_in_map[i] = g_text_color[proc->origin_champ->index_player];
}

int			is_a_process(t_all *all, int pc)
{
	int			i;
	t_process	*proc;

	proc = all->stack_proc;
	while (1)
	{
		if (pc == proc->pc)
			return ((unsigned int)proc->origin_champ->index_player + 1);
		if (!(proc = proc->next))
			break ;
	}
	return (0);
}

char		*give_color(t_champ *champ)
{
	return (g_text_color[champ->index_player + 4]);
}
