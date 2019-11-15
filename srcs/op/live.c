#include "vm_corewar.h"

void    	op_live(t_all *all, t_process *proc)
{
	t_champ	*champ;

	parse_arg_op(all, proc);
	champ = get_champ(proc->op.params[0], all);
	// printf("live for champ (%p) %d proc->op.params[0] %d\n", champ, champ ? champ->index : 0, proc->op.params[0]);
	if (champ)
	{
		// if (!(all->flag & FLAG_RESUME))
		// 	printf("un processus dit que le joueur %d(%s) est en vie\n", proc->op.params[0], champ->name);
		// else
		// 	printf("P	%d| live %d\n", champ->index, proc->op.params[0]);
		all->last_player_alive = champ;
		proc->flag_live = 1;
		all->nb_live++;
	}
	// affiche_new_pc();
}
