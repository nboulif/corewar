/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:10:31 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/08 16:28:08 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


int				main(int argc, char **argv)
{
	t_prog	*prog;
	t_data	*data;

	if (!(prog = init_prog(argc, argv)))
		return (1);
	if (get_header(prog))
		return (free_prog(prog) + 1);
	if (prog->nb_line <= 0)
		return (printf("Empty program\n") + free_prog(prog));
	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return (printf("Error Malloc Data\n") + free_prog(prog));
	data->pc = 0;
	data->nb_octet = 0;
	
	if (!program_parser(prog, data))
	{
		if (prog->prog_size == 0)
			return (printf("Empty program\n") + free_prog(prog));
		if (prog->debug)
			print_debug(prog);
		else
			write_file(prog);
	}
	free_data(data);
	free_prog(prog);
	return (0);
}
