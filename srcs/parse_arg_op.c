# include "vm_corewar.h"

int		give_next_arg(t_all *all, int size_arg, t_process *proc)
{
	int arg;
	int i;

	i = 0;
	arg = all->map[proc->pc];
	move_pc(&proc->pc, 1);	
	while (++i < size_arg)
	{
		arg = arg << 8;
		arg |= all->map[proc->pc];
		move_pc(&proc->pc, 1);
	}
	// il faut pas reverse, le int est legal
	return (arg);
}

void	parse_arg_op(t_all *all, t_process *proc)
{
	static int	tab[3] = {T_REG, T_DIR, T_IND};
	static int 	size_arg[5] = {0, 1, 2, 0, 4};
	int size_cur_arg;
	int i;

	i = -1;
	ft_memcpy(&proc->op, &op_tab[all->map[proc->pc]], sizeof(t_op));
	if (op_tab[all->map[proc->pc]].codage_octal)
	{
		move_pc(&proc->pc, 1);
		// printf("codage_octal\n");s
		while (++i < 3)
		{
			if (!(((all->map[proc->pc] & 0b11000000) >> 6) ^ tab[i]))
				proc->op.type_of_params[0] = tab[i];
			if (!(((all->map[proc->pc] & 0b110000) >> 4) ^ tab[i]))
				proc->op.type_of_params[1] = tab[i];
			if (!(((all->map[proc->pc] & 0b1100) >> 2) ^ tab[i]))
				proc->op.type_of_params[2] = tab[i];
		}
		i = -1;
	}
	move_pc(&proc->pc, 1);
	while (++i < proc->op.nb_params)
	{
		// printf("type_of_params[%.2d]\n", i);
		// print_bit(proc->op.type_of_params[i]);
		// printf("\n");
		if (proc->op.type_of_params[i] == T_DIR)
			size_cur_arg = 2 + 2 * (!proc->op.dir_size);
		else
			size_cur_arg = size_arg[proc->op.type_of_params[i]];
		proc->op.params[i] = give_next_arg(all, size_cur_arg, proc);
	}
}

