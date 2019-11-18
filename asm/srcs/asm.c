/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:10:31 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/18 17:58:49 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			free_data(t_data *data, t_prog *prog)
{
	int i;

	i = 0;
	while (data)
	{
		free(data->line);
		free(data->label);
		free(data->params);
		data = data->next;
	}
	free(data);
	free(prog->line);
	free(prog->name);
	free(prog->comment);
	free(prog);
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
		return (printf(ERROR_EMPTY_PROG));
	data = (t_data*)malloc(sizeof(t_data));
	data->pc = 0;
	data->nb_octet = 0;
	if (!program_parser(prog, data))
	{
		if (prog->prog_size == 0)
			return (printf(ERROR_EMPTY_PROG));
		if (prog->debug)
			print_debug(prog);
		else
			write_file(prog);
	}
	free_data(data, prog);
	return (0);
}
