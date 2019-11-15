# include "vm_corewar.h"

int		give_next_arg(t_all *all, int size_arg, t_process *proc)
{
	int arg;
	int i;

	i = 0;
	if (!size_arg)
		return (0);
	arg = all->map.character[proc->pc];
	move_pc(&proc->pc, 1);
	while (++i < size_arg)
	{
		arg = arg << 8; 
		arg |= all->map.character[proc->pc] & 0x000000FF;
		move_pc(&proc->pc, 1);
	}
	// il faut pas reverse, le int est legal
	return (arg);
}

int		parse_arg_op(t_all *all, t_process *proc)
{
	static int	tab[6] = {T_REG, T_DIR, T_IND, F_REG, F_DIR, F_IND};
	static int 	size_arg[5] = {0, 1, 0, 0, 2};
	int size_cur_arg;
	int i;
	int ret;

	printf("****************************************opc %d\n", proc->op.opc);
	ret = 1;
	i = -1;
	if (op_tab[all->map.character[proc->pc]].codage_octal)
	{
		move_pc(&proc->pc, 1);
		ft_bzero(proc->op.type_of_params, sizeof(int) * 3);
		ft_bzero(proc->op.flags_params, sizeof(int) * 3);
		while (++i < 3)
		{
			printf("tab[%d]: %d\n", i, tab[i]);
			printf("ocatal %d\n", all->map.character[proc->pc]);
			if ((((all->map.character[proc->pc] & 0b11000000) >> 6) == tab[i]))
			{
				printf("1\n");
				proc->op.flags_params[0] = tab[i + 3];
				printf("tab %d\n", tab[i + 3]);
				proc->op.type_of_params[0] = tab[i];
			}
			if ((((all->map.character[proc->pc] & 0b110000) >> 4) == tab[i]))
			{
				printf("2\n");
				proc->op.flags_params[1] = tab[i + 3];
				printf("tab %d\n", tab[i + 3]);
				proc->op.type_of_params[1] = tab[i];
			}
			if ((((all->map.character[proc->pc] & 0b1100) >> 2) == tab[i]))
			{
				printf("3\n");
				proc->op.flags_params[2] = tab[i + 3];
				printf("tab %d\n", tab[i + 3]);
				proc->op.type_of_params[2] = tab[i];
			}
		}
		i = -1;
	}
	// si jms codage octal pourri
	if ((!(proc->op.flags_params[0] & op_tab[proc->op.opc].flags_params[0]) && op_tab[proc->op.opc].nb_params > 0) ||
		(!(proc->op.flags_params[1] & op_tab[proc->op.opc].flags_params[1]) && op_tab[proc->op.opc].nb_params > 1) ||
		(!(proc->op.flags_params[2] & op_tab[proc->op.opc].flags_params[2]) && op_tab[proc->op.opc].nb_params > 2))
		ret = 0;
	move_pc(&proc->pc, 1);
	printf("%d\n", proc->op.nb_params);
	while (++i < proc->op.nb_params)
	{
		if (proc->op.type_of_params[i] == T_DIR)
			size_cur_arg = 2 + 2 * (!proc->op.dir_size);
		else
		{
			printf("i %d flag %d\n", i, proc->op.flags_params[i]);
			size_cur_arg = size_arg[proc->op.flags_params[i]];
			printf("size %d\n", size_cur_arg);
		}
		proc->op.params[i] = give_next_arg(all, size_cur_arg, proc);
		if (proc->op.type_of_params[i] == T_REG)
			if (proc->op.params[i] > REG_NUMBER || proc->op.params[i] < 1)
				ret = 0;
	}
	printf("---------opc %d, %d, %d, %d\n", proc->op.opc, proc->op.params[0], proc->op.params[1], proc->op.params[2]);
	// moveTo(20, 64 * 3 + 20);
	// printf("ret %d proc->op.nb_params %d\n", ret,proc->op.nb_params);
	return (ret);
}

