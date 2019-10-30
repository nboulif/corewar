#include "vm_corewar.h"

void    	op_live(t_all *all, t_process *proc)
{
	t_champ	*champ;

	if (!proc->to_do)
	{
		// ft_bzero(proc->op.params, 3 * sizeof(int));
		ft_memcpy(&proc->op, &op_tab[all->map[proc->pc]], sizeof(t_op));
		proc->wait = proc->op.cycles - 1;
	}
	else
	{
		parse_arg_op(all, proc);
		champ = get_champ(proc->op.params[0], all);
		if (champ)
		{
			// if (!(all->flag & FLAG_RESUME))
			// 	printf("un processus dit que le joueur %d(%s) est en vie\n", proc->op.params[0], champ->name);
			// else
			// 	printf("P	%d| live %d\n", champ->index, proc->op.params[0]);
			all->last_player_alive = champ;
			proc->flag_live = 1;
		}
		// affiche_new_pc();
	}
	proc->to_do = 1 - proc->to_do;
}
