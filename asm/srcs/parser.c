/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 13:06:40 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/06 16:48:53 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				program_parser(t_prog *prog)
{
	t_data	*data;
	t_data	*old_data;

	old_data = NULL;
	data = NULL;
	while (get_next_line(prog->fd, &prog->line) > 0)
	{
		prog->i = 0;
		prog->nb_line++;
		skip_chars(prog->line, &prog->i, " \t");
		if ((!prog->line || !prog->line[prog->i] ||
			prog->line[prog->i] == '#') && !free_str(prog->line))
			continue;
		else if (prog->line[prog->i] == '.')
			return (err_default(prog,
				ERROR_COMMAND_IN_PROG) + free_str(prog->line));
			old_data = data;
		if (!(data = parse_commands(prog)))
			return (ERROR);
		get_pc(prog, old_data, data);
	}
	free(prog->line);
	prog->prog_size = data ? data->pc + data->nb_octet : 0;
	close(prog->fd);
	return (0);
}
