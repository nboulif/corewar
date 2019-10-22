#include "vm_corewar.h"

static void			handle_player_with_number(int *i, int argc, char **argv,
	t_all *all)
{
	*i += 3;
	if (*i > argc)
		print_error_and_exit(INCOMPLETE_CHAMP);
	parse_champ(all, argv[*i - 2], argv[*i - 1]);
}

static int			is_valid_flag(char *flag)
{
	char			**synonyms;

	synonyms = flags_syn[*flag];
	if (!flag[0] || !synonyms)
		return (0);
	if (!flag[1])
		return (1);
	while (*synonyms)
	{
		if (!ft_strcmp(flag, *synonyms))
			return (1);
		(*synonyms)++;
	}
	return (0);
}

static int			handle_flag(int *i, int argc, char **argv, t_all *all)
{
	unsigned int	out;

	if (!is_valid_flag(&argv[*i][1]))
		parse_champ(all, NULL, argv[*i]);
	else if (out == FLAG_NUMBER)
	{
		handle_player_with_number(i, argc, argv, all);
		return (0);
	}
	return (out);
}

int					main(int argc, char **argv)
{
	t_all			all;
	int				i;

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
