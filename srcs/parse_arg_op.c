# include "vm_corewar.h"

char	tab_of_printed_value_arg[16][3][3] =
								{
									{{0,0,0},{0,0,0},{0,0,0}},
									{{0,0,1},{0,0,0},{0,0,0}},
									{{0,0,0},{0,0,0},{0,0,0}},
									{{0,0,1},{0,0,1},{0,0,0}},
									{{0,0,1},{0,0,1},{0,0,0}},
									{{1,0,1},{1,0,1},{0,0,0}},
									{{1,0,1},{1,0,1},{0,0,0}},
									{{1,0,1},{1,0,1},{0,0,0}},
									{{0,0,0},{0,0,0},{0,0,0}},
									{{1,1,1},{1,1,1},{0,0,0}},
									{{0,0,0},{1,0,1},{1,0,0}},
									{{0,0,0},{0,0,0},{0,0,0}},
									{{0,0,1},{0,0,0},{0,0,0}},
									{{1,1,1},{1,1,1},{0,0,0}},
									{{0,0,0},{0,0,0},{0,0,0}},
									{{0,0,0},{0,0,0},{0,0,0}} 
								};

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
	return (arg);
}

int		parse_arg_op(t_all *all, t_process *proc)
{
	static int	tab[6] = {T_REG, T_DIR, T_IND, F_REG, F_DIR, F_IND};
	static int 	size_arg[5] = {0, 1, 0, 0, 2};
	int size_cur_arg;
	int i;
	int ret;

	ret = 1;
	i = -1;

	int pc_to_read = proc->pc;

	if (proc->op.codage_octal)
	{
		move_pc(&proc->pc, 1);
		ft_bzero(proc->op.type_of_params, sizeof(int) * 3);
		ft_bzero(proc->op.flags_params, sizeof(int) * 3);
		while (++i < 3)
		{
			if ((((all->map.character[proc->pc] & 0b11000000) >> 6) == tab[i]))
			{
				proc->op.flags_params[0] = tab[i + 3];
				proc->op.type_of_params[0] = tab[i];
			}
			if ((((all->map.character[proc->pc] & 0b110000) >> 4) == tab[i]))
			{
				proc->op.flags_params[1] = tab[i + 3];
				proc->op.type_of_params[1] = tab[i];
			}
			if ((((all->map.character[proc->pc] & 0b1100) >> 2) == tab[i]))
			{
				proc->op.flags_params[2] = tab[i + 3];
				proc->op.type_of_params[2] = tab[i];
			}
		}
		i = -1;
		if ((!(proc->op.flags_params[0] & g_op_tab[proc->op.opc].flags_params[0]) && g_op_tab[proc->op.opc].nb_params > 0) ||
			(!(proc->op.flags_params[1] & g_op_tab[proc->op.opc].flags_params[1]) && g_op_tab[proc->op.opc].nb_params > 1) ||
			(!(proc->op.flags_params[2] & g_op_tab[proc->op.opc].flags_params[2]) && g_op_tab[proc->op.opc].nb_params > 2))
			ret = 0;
	}
	move_pc(&proc->pc, 1);
	while (++i < proc->op.nb_params)
	{
		if (proc->op.type_of_params[i] == T_DIR)
			size_cur_arg = 2 + 2 * (!proc->op.dir_size);
		else
		{
			size_cur_arg = size_arg[(int)proc->op.flags_params[i]];
		}
		proc->op.params[i] = give_next_arg(all, size_cur_arg, proc);
		if (proc->op.type_of_params[i] == T_REG)
			if (proc->op.params[i] > REG_NUMBER || proc->op.params[i] < 1)
				ret = 0;
	}
	if (ret && proc->op.opc != 16)
	{
		i = -1;
		if (all->flag & FLAG_RESUME)
			ft_printf("P %4d | %s ", proc->index, proc->op.name);
		while (++i < proc->op.nb_params)
		{
			if (all->flag & FLAG_RESUME && ret)
			{
				if (proc->op.type_of_params[i] == T_REG && !tab_of_printed_value_arg[proc->op.opc - 1][i][T_REG - 1] && !(proc->op.opc == 3 && i == 1 ))
					ft_printf("r");
				ft_printf(i == proc->op.nb_params - 1 && proc->op.opc != 9 && proc->op.opc != 12 && proc->op.opc != 15 ? "%d\n" : "%d ",
				tab_of_printed_value_arg[proc->op.opc - 1][i][proc->op.type_of_params[i] - 1] ?
				value_of_arg(all, proc, pc_to_read, i) : proc->op.params[i]);
			}
		}
	}
	return (ret);
}

