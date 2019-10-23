#include "vm_corewar.h"

void    	op_live(t_all *all, t_process *proc)
{
	t_champ	*champ;

	parse_arg_op(all, proc);
	champ = get_champ(proc->op.params[0], all);
	if (champ)
	{
		ft_printf("un processus dit que le joueur %d(%s) est en vie\n", proc->op.params[0], champ->name);
		all->last_player_alive = champ;
		proc->flag_live = 1;
		proc->wait = proc->op.cycles - 1;
	}
}
