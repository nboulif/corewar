/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:10:31 by nsondag           #+#    #+#             */
/*   Updated: 2019/10/17 16:07:20 by nsondag          ###   ########.fr       */
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
		return (1);
	if (!prog->nb_line)
		return (printf("%s[001:001] %s\n", SYNTAX, END));
	data = (t_data*)malloc(sizeof(t_data));
	data->pc = 0;
	data->nb_octet = 0;
	prog->file_name = argv[1];
	if (!program_parser(prog, data))
	{
		if (!prog->i)
			return (printf("%s[%0.3d:%0.3d] %s\n",
						SYNTAX, prog->nb_line, prog->i, END));
		else if (prog->debug)
			print_debug(prog);
		else
			write_file(prog);
	}
	return (0);
}
