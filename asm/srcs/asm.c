/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:10:31 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/06 16:48:55 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		open_file(t_prog *prog, int argc, char **argv)
{
	if (argc < 2)
	{
		printf("%s%s%s%s", USAGE1, USAGE2, USAGE3, USAGE4);
		return (1);
	}
	if (argc > 2 && *argv[1] == '-')
	{
		prog->debug = 0;
		if (!ft_strcmp("-a", argv[1]))
			prog->debug = 1;
		prog->fd = open(argv[2], O_RDONLY);
		if (prog->fd < 0)
			return (printf("Can't read source file %s\n", argv[2]));
	}
	else
	{
		prog->fd = open(argv[1], O_RDONLY);
		if (prog->fd < 0)
			return (printf("Can't read source file %s\n", argv[1]));
	}
	return (0);
}

static t_prog	*init_prog(int argc, char **argv)
{
	t_prog	*prog;

	if (!(prog = (t_prog *)malloc(sizeof(t_prog))))
		return (NULL);
	if (!(prog->line = (char *)malloc(sizeof(*prog->line) * 1)))
	{
		free(prog);
		return (NULL);
	}
	if (open_file(prog, argc, argv))
	{
		free(prog->line);
		free(prog);
		return (NULL);
	}
	prog->nb_line = 0;
	prog->name = NULL;
	prog->comment = NULL;
	prog->list_data = NULL;
	return (prog);
}

int				main(int argc, char **argv)
{
	t_prog	*prog;
	t_data	*data;

	if (!(prog = init_prog(argc, argv)))
		return (1);
	if (get_header(prog))
		return (1);
	if (prog->nb_line <= 0)
		return (printf("%s[001:001] %s\n", SYNTAX, END));
	data = (t_data*)malloc(sizeof(t_data));
	data->pc = 0;
	data->nb_octet = 0;
	prog->file_name = argv[1];
	if (!program_parser(prog, data))
	{
		if (!prog->i)
		{
			return (printf("%s[%0.3d:%0.3d] %s\n",
						SYNTAX, prog->nb_line, prog->i, END));
		}
		else if (prog->debug)
			print_debug(prog);
		else
			write_file(prog);
	}
	return (0);
}
