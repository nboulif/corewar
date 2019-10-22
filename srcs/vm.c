#include "vm_corewar.h"

void		next_action(t_all *all, t_process *current_process)
{
	if (current_process->wait)
	{
		current_process->wait--;
		return ;
	}
}

int		check_nb_live(t_all *all)
{
	static t_champ	*tab_of_alive_champ[4];
	t_process		*process;
	int				i;

	i = -1;
	if (all->nb_alive == -1)
	{
		all->nb_alive = all->nb_champ;
		while (++i < all->nb_champ)
			tab_of_alive_champ[i] = &all->champ[i];
		i = -1;
	}
	while (++i < all->nb_alive)
		if (tab_of_alive_champ[i]->nb_live < NBR_LIVE)
		{
			tab_of_alive_champ[i]->alive = 0;
			tab_of_alive_champ[i--] = tab_of_alive_champ[--all->nb_alive];
			if (all->nb_alive == 0)
				return (0);
		}
	i = -1;
	while (++i < all->stack_champ->n_items)
		if (!(process = (t_process*)ft_array_get(all->stack_champ, i)) &&
			(!process->origin_champ->alive || !process->flag_live))
			ft_array_remove(all->stack_champ, i--, process);
	return (1);
}

void		vm(t_all *all)
{
	int 	cycle;
	int		i;
	int		total_cycle;

	cycle = 0;
	total_cycle = 0;
	if (!(all->map = malloc(sizeof(char) * MEM_SIZE)))
		print_error_and_exit(MALLOC_ERROR);
	init_vm(all);
	while (total_cycle < all->cycles_before_exit)
	{
		i = 0;
		while (i < all->stack_champ->n_items)
			next_action(all, (t_process*)ft_array_get(all->stack_champ, i++));
		if (cycle++ == all->cycle_to_die)
		{
			if (!check_nb_live(all) || !all->stack_champ->n_items ||
					all->cycle_to_die <= CYCLE_DELTA)
				break ;
			if (all->nb_live || all->nb_check++ > MAX_CHECKS)
			{
				all->cycle_to_die -= CYCLE_DELTA;
				total_cycle += cycle;
				cycle = 0;
			}
		}
	}
	ft_printf("le joueur %d(%s) a gagne\n", all->last_player_alive->index, all->last_player_alive->name);
}
