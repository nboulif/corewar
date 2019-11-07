# include "vm_corewar.h"

int		give_next_arg(t_all *all, int size_arg, t_process *proc)
{
	int arg;
	int i;

	i = 0;
	arg = all->map.character[proc->pc];
	move_pc(&proc->pc, 1);
	while (++i < size_arg)
	{
		arg = arg << 8;
		arg |= all->map.character[proc->pc];
		move_pc(&proc->pc, 1);
	}
	// il faut pas reverse, le int est legal
	return (arg);
}

int		parse_arg_op(t_all *all, t_process *proc)
{
	static int	tab[3] = {T_REG, T_DIR, T_IND};
	static int 	size_arg[4] = {0, 1, 0, 2};
	int size_cur_arg;
	int i;
	int ret;

	ret = 1;
	i = -1;
	if (op_tab[all->map.character[proc->pc]].codage_octal)
	{
		move_pc(&proc->pc, 1);
		while (++i < 3)
		{
			if ((((all->map.character[proc->pc] & 0b11000000) >> 6) == tab[i]))
				proc->op.type_of_params[0] = tab[i];
			if ((((all->map.character[proc->pc] & 0b110000) >> 4) == tab[i]))
				proc->op.type_of_params[1] = tab[i];
			if ((((all->map.character[proc->pc] & 0b1100) >> 2) == tab[i]))
				proc->op.type_of_params[2] = tab[i];
		}
		i = -1;
	}
	// si jms codage octal pourri
	if ((!(proc->op.type_of_params[0] & op_tab[proc->op.opc].type_of_params[0]) && op_tab[proc->op.opc].nb_params > 0) ||
		(!(proc->op.type_of_params[1] & op_tab[proc->op.opc].type_of_params[1]) && op_tab[proc->op.opc].nb_params > 1) ||
		(!(proc->op.type_of_params[2] & op_tab[proc->op.opc].type_of_params[2])  && op_tab[proc->op.opc].nb_params > 2))
		ret = 0;
	move_pc(&proc->pc, 1);
	while (++i < proc->op.nb_params)
	{
		if (proc->op.type_of_params[i] == T_DIR)
			size_cur_arg = 2 + 2 * (!proc->op.dir_size);
		else
			size_cur_arg = size_arg[proc->op.type_of_params[i]];
		proc->op.params[i] = give_next_arg(all, size_cur_arg, proc);
		// printf("proc->op.params[%d] %d proc->op.type_of_params[i] %d\n", i, proc->op.params[i], proc->op.type_of_params[i]);
		if (proc->op.type_of_params[i] == T_REG)
			if (proc->op.params[i] > REG_NUMBER || proc->op.params[i] < 1)
				ret = 0;
	}
	// moveTo(20, 64 * 3 + 20);
	// printf("ret %d proc->op.nb_params %d\n", ret,proc->op.nb_params);
	return (ret);
}

