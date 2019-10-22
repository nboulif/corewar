#include "vm_corewar.h"

int next_action(t_all *all, int i_champ)
{

}

int		init_vm(t_all *all)
{

}

int		vm(t_all *all)
{
	int cycle;
	int i_champ;

	cycle = 0;
	while (cycle)
	{
		i_champ = 0;
		while (i_champ < all->nb_champ)
			next_action(all, i_champ++);
		cycle++;
	}
}