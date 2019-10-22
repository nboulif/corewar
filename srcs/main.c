#include "vm_corewar.h"

static void			handle_player_with_number(int *i, int argc, char **argv,
	t_all *all)
{
	*i += 2;
	if (*i >= argc)
		print_error_and_exit(INCOMPLETE_ARG);
	parse_champ(all, argv[*i - 1], argv[*i]);
}

static void			handle_dump(int *i, int argc, char **argv, t_all *all)
{
	*i += 1;
	if (*i >= argc)
		print_error_and_exit(INCOMPLETE_ARG);
	if (!check_index(argv[*i]))
		print_error_and_exit(DUMP_CYCLE_AMOUNT_ERROR);
	all->cycles_before_exit = ft_atoi(argv[*i]);
}

static int			is_valid_flag(char *flag)
{
	if (flags[*flag] && !flag[1])
		return (1);
	return (flags_syn[*flag] && !ft_strcmp(flag, flags_syn[*flag]));
}

static int			handle_flag(int *i, int argc, char **argv, t_all *all)
{
	unsigned int	out;

	out = flags[argv[*i][1]];
	if (!is_valid_flag(&argv[*i][1]))
		parse_champ(all, NULL, argv[*i]);
	else if (out == FLAG_NUMBER)
	{
		handle_player_with_number(i, argc, argv, all);
		return (0);
	}
	else if (out == FLAG_DUMP)
		handle_dump(i, argc, argv, all);
	return (out);
}

void				usage(void)
{
	ft_printf("Usage ./corewar [-t] [-v] [-d | -dump N] [[-n N] \
		<champion.cor>] <...>\n");
	ft_printf(
		"	-t			: enable threads\n\
			-v			: enable visualization\n\
			-d -dump N	: at the end of nbr_cycles of executions, dump the \
				memory on the standard output and quit the game. The memory is \
				dumped in the hexadecimal format with 32 octets per line.\
			-n N		: sets the number of the next player. If non-existent, \
				the player will have the next available number in the order of \
				the parameters. The last player will have the first process in \
				the order of execution.");
}

int					main(int argc, char **argv)
{
	t_all			all;
	int				i;

	if (argc == 1)
	{
		usage();
		return (0);
	}
	ft_bzero(&all, sizeof(t_all));
	config_flags();
	config_flags_syn();
	i = 0;
	while (++i < argc)
	{
		if (*argv[i] == '-')
			all.flag |= handle_flag(&i, argc, argv, &all);
		else
			parse_champ(&all, NULL, argv[i]);
	}
	//execute
	//free_all
	return (0);
}
