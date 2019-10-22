#include "vm_corewar.h"

char				args[2][10] = {
	"-dump",
	"-n"
};

int					ft_error_invalid_arg()
{
	return (-1);
}

void				ft_handle_dump(char *arg)
{
	return ;
}

int					main(int argc, char **argv)
{
	t_all			all;
	int				i;

	ft_bzero(&all, sizeof(t_all));
	if (argc < 4)
		return (ft_error_invalid_arg());
	if (!ft_strcmp(args[0], argv[1]))
	{
		all.flag |= DUMP;
		ft_handle_dump(argv[2]);
		i = 3;
	}
	else
		i = 1;
	while (i < argc)
	{ // gerer le fait que -n est facultatif ( dans ce cas la vm doit assigner un numero d'ordre elle meme )
		if (ft_strcmp(args[1], argv[i - 2]))
			return (ft_error_invalid_arg());
		parse_champ(&all, argv[i - 1], argv[i]);
		i += 3;
	}
	return (0);
}