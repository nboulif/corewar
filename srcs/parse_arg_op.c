# include "vm_corewar.h"

int		rev_short_byte(short nb)
{
	return (nb << 8 | nb >> 8);
}

int		give_next_arg(t_all *all, int size_arg, t_process *proc)
{
	int arg;
	int i;

	i = 0;
	arg |= all->map[proc->pc];
	move_pc(&proc->pc, 1);	
	while (++i < size_arg)
	{
		arg = arg << 8;
		arg |= all->map[proc->pc];
		move_pc(&proc->pc, 1);
	}
	if (size_arg == 2)
		arg = rev_short_byte((short)arg);
	else if (size_arg == 4)
		arg = rev_int_byte(arg);
	return (arg);
}

void	parse_arg_op(t_all *all, t_process *proc, t_op *op)
{
	static int	tab[3] = {T_REG, T_DIR, T_IND};
	static int 	size_arg[5] = {0, 1, 2, 0, 4};
	int size_cur_arg;
	int i;
	int x;

	i = -1;
	ft_memcpy(op, &op_tab[all->map[proc->pc]], sizeof(t_op));
	if (op_tab[all->map[proc->pc]].codage_octal)
	{
		move_pc(&proc->pc, 1);
		while (++i < 3)
		{
			if (!((all->map[proc->pc] & 0b11000000) >> 6) ^ tab[i])
				op->type_of_params[0] = tab[i];
			if (!((all->map[proc->pc] & 0b110000) >> 4) ^ tab[i])
				op->type_of_params[1] = tab[i];
			if (!((all->map[proc->pc] & 0b1100) >> 2) ^ tab[i])
				op->type_of_params[2] = tab[i];
		}
		i = -1;
	}
	move_pc(&proc->pc, 1);
	x = -1;
	while (++i < op->nb_params)
	{
		if (op->type_of_params[i] == T_DIR)
			size_cur_arg = 2 + 2 * (!op->dir_size);
		else
			size_cur_arg = size_arg[op->type_of_params[i]];
		op->params[i] = give_next_arg(all, size_cur_arg, proc);
		x = -1;
	}
}

