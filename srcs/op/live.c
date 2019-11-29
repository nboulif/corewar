#include "vm_corewar.h"

void    	op_live(t_all *all, t_process *proc)
{
	t_champ	*champ;

	parse_arg_op(all, proc);
	champ = get_champ(proc->op.params[0], all);
	proc->flag_live = 1;
	all->nb_live++;
	if (champ)
		all->last_player_alive = champ;
}
