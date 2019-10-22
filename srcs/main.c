#include "vm_corewar.h"

static void			handle_player_with_number(int *i, int argc, char **argv,
	t_all *all)
{
	*i += 2;
	if (*i >= argc)
		print_error_and_exit(INCOMPLETE_CHAMP);
	parse_champ(all, argv[*i - 1], argv[*i]);
}

static void			handle_dump(int *i, int argc, char **argv, t_all *all)
{
	
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
	ft_printf("Usage ./corewar [-t] [-v] [-d | -dump] [-n]");
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
