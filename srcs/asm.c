/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:10:31 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/18 16:29:03 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h" 

unsigned int convert_to_big_endian(unsigned int x)
{
	return (((x>>24) & 0x000000ff) | ((x>>8) & 0x0000ff00) |
	((x<<8) & 0x00ff0000) | ((x<<24) & 0xff000000));
}

int magic_number(t_prog *header)
{
	int fd;
	unsigned int byte = COREWAR_EXEC_MAGIC;
	size_t length;

	length = ft_strlen(header->name);
	//printf("%zu\n", length);
	byte = convert_to_big_endian(byte);
	fd = open(header->name, O_CREAT | O_RDWR, 0644);
	write(fd, &byte, 4);
	write(fd, header->name, PROG_NAME_LENGTH);
	byte = 0;
	write(fd, &byte, 4);
	length = convert_to_big_endian(length);
	write(fd, &length, 4);
	write(fd, header->comment, COMMENT_LENGTH);
	write(fd, &byte, 4);
	close(fd);
	return (0);
}

int	main(int argc, char **argv)
{
	t_prog	*prog;
	t_data	*data;

	if (!(prog = init_prog(argc, argv)))
		return (1);
	if (get_header(prog))
		return (1);
	if (!prog->nb_line)
		return (printf("Syntax error at token [TOKEN][001:001] END \"(null)\"\n"));
		
	data = (t_data*)malloc(sizeof(t_data));
	data->pc = 0;
	data->nb_octet = 0;
	
	if (!program_parser(prog, data))
	{
		if (!prog->i)
			return (printf("Syntax error at token [TOKEN][%0.3d:%0.3d] END \"(null)\"\n", 
				prog->nb_line, prog->i));
		else if (prog->debug)
			print_debug(prog);
		else
			printf("Writing\n");
	}
	return (0);
}
