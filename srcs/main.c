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
	ft_putstr(
"Usage ./corewar [-t] [-v] [-d | -dump N] [[-n N] \
<champion.cor>] <...>\n\
	-t		: enable threads\n\
	-v		: enable visualization\n\
	-d -dump N	: at the end of nbr_cycles of executions, dump the \
memory on the standard output and quit the game. The memory is \
dumped in the hexadecimal format with 32 octets per line.\n\
	-n N		: sets the number of the next player. If non-existent, \
the player will have the next available number in the order of \
the parameters. The last player will have the first process in \
the order of execution.\n");
	exit(1);
}

int					main(int argc, char **argv)
{
	t_all			all;
	int				i;

	if (argc == 1)
		usage();
	ft_bzero(&all, sizeof(t_all));
	all.nb_alive = -1;
	all.cycle_to_die = CYCLE_TO_DIE;
	all.cycles_before_exit = -1;
	config_flags();
	config_flags_syn();
	i = 0;
	printf("Introducing contestants...\n");
	while (++i < argc)
	{
		if (*argv[i] == '-')
			all.flag |= handle_flag(&i, argc, argv, &all);
		else
		{
			parse_champ(&all, NULL, argv[i]);
			printf("* Player %zu, weighing %zu bytes, \"%s\" (\"%s\") !\n", all.nb_champ, all.champ[all.nb_champ - 1].size_exec, all.champ[all.nb_champ - 1].name, all.champ[all.nb_champ - 1].comment);
		}
	}
	printf("\e[?25l");
	vm(&all);
	//execute
	//free_all
	return (0);
}
