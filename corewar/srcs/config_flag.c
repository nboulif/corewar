/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:16:02 by nsondag           #+#    #+#             */
/*   Updated: 2019/12/20 16:49:20 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

int		handle_flag(int *i, int argc, char **argv, t_all *all)
{
	unsigned int	out;

	out = g_flags[(int)argv[*i][1]];
	if (!is_valid_flag(&argv[*i][1]))
		parse_champ(all, NULL, argv[*i]);
	else if (out == FLAG_NUMBER)
	{
		*i += 2;
		if (*i >= argc)
			print_error_and_exit(INCOMPLETE_ARG);
		parse_champ(all, argv[*i - 1], argv[*i]);
		return (0);
	}
	else if (out == FLAG_DUMP || out == FLAG_DUMP64)
		handle_dump(i, argc, argv, all);
	return (out);
}

void	config_flags(void)
{
	g_flags['d'] = FLAG_DUMP;
	g_flags['n'] = FLAG_NUMBER;
	g_flags['t'] = FLAG_THREAD;
	g_flags['v'] = FLAG_VISU;
	g_flags['r'] = FLAG_RESUME;
	g_flags['c'] = FLAG_CYCLE;
	g_flags['x'] = FLAG_DEATH;
	g_flags['L'] = FLAG_LIVE;
	g_flags['D'] = FLAG_DUMP64;
}

void	config_flags_syn(void)
{
	g_flags_syn['d'] = "dump";
}
