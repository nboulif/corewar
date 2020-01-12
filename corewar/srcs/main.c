/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 13:46:29 by nsondag           #+#    #+#             */
/*   Updated: 2020/01/11 18:56:20 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		handle_dump(int *i, int argc, char **argv, t_all *all)
{
	*i += 1;
	if (*i >= argc)
		print_error_and_exit(INCOMPLETE_ARG);
	if (!check_index(argv[*i]))
		print_error_and_exit(DUMP_CYCLE_AMOUNT_ERROR);
	all->cycles_before_exit = ft_atoi(argv[*i]);
}

int			is_valid_flag(char *flag)
{
	if (g_flags[(int)*flag] && !flag[1])
		return (1);
	return (g_flags_syn[(int)*flag] &&
			!ft_strcmp(flag, g_flags_syn[(int)*flag]));
}

void		usage(void)
{
	ft_putstr(
"Usage ./corewar [-c][-L][-r][-v][-x] [-d | -dump N] [-D | N][[-n N] \
<champion.cor>] <...>\n\
	-c		: Show cycles\n\
	-L		: Show lives\n\
	-r		: Show operations\n\
	-x		: Show deaths\n\
	-v		: enable visualization\n\
	-d -dump N	: at the end of nbr_cycles of executions, dump the \
memory on the standard output and quit the game. The memory is \
dumped in the hexadecimal format with 32 octets per line.\n\
	-D  N		: at the end of nbr_cycles of executions, dump the \
memory on the standard output and quit the game. The memory is \
dumped in the hexadecimal format with 64 octets per line.\n\
	-n N		: sets the number of the next player. If non-existent, \
the player will have the next available number in the order of \
the parameters. The last player will have the first process in \
the order of execution.\n");
	exit(1);
}

void		print_comment(t_all *all)
{
	size_t i;

	i = -1;
	while (i++ < all->nb_champ)
	{
		ft_printf("* Player %zu, weighing %zu bytes, \"%s\" (\"%s\") !\n",
			i, all->champ[i].size_exec, all->champ[i].name,
			all->champ[i].comment);
	}
}

int			main(int argc, char **argv)
{
	t_all			all;
	pthread_t		thread;
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
	ft_printf("Introducing contestants...\n");
	while (++i < argc)
		if (*argv[i] == '-')
		{
			all.flag |= handle_flag(&i, argc, argv, &all);
			if (all.flag & FLAG_VISU)
				all.flag = FLAG_VISU;
		}
		else
			parse_champ(&all, NULL, argv[i]);
	if (all.flag & FLAG_VISU)
	{
		// initscr();
		// noecho();
		// curs_set(FALSE);
		// if (pthread_create(&thread, NULL, check_pause, NULL) == -1)
		// 	exit(ft_printf("Thread create fail\n") * 0 + 1);
		ft_printf("\e[?25l");
	}
	else
		print_comment(&all);	
	vm(&all);
	return (0);
}
