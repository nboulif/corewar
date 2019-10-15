/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:10:31 by nsondag           #+#    #+#             */
/*   Updated: 2019/10/15 17:28:19 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h" 

size_t convert_to_big_endian(size_t x)
{
	return (((x>>24) & 0x000000ff) | ((x>>8) & 0x0000ff00) |
	((x<<8) & 0x00ff0000) | ((x<<24) & 0xff000000));
}

size_t convert_to_big_endian2(size_t x)
{
	return ((((x>>8) & 0x00ff) |
	((x<<8) & 0xff00)));
}

int	write_program(t_prog *prog, int fd)
{
	t_data *data;
	int i;
	int size;

	data = prog->list_data;
	while (data)
	{
		write(fd, &data->op->opc, 1);
		if (data->codage_octal != 128)
			write(fd, &data->codage_octal, 1);
		size_t byte;
		i = -1;
		while (++i < 3)
		{
			size = (data->codage_octal >> (2 * (3 - i))) & 3;
			if (size == 2 && !data->op->dir_size)
			{
				byte = convert_to_big_endian(data->val_param[i]);
				size = 4;
			}
			else if (size == 2)
				byte = convert_to_big_endian2(data->val_param[i]);
			else
				byte = data->val_param[i];
			write(fd, &byte, size);
		}
		data = data->next;
	}
	return (0);
}

int magic_number(t_prog *header)
{
	int fd;
	int i;
	size_t byte = COREWAR_EXEC_MAGIC;
	size_t length;
	
	length = header->prog_size;
	byte = convert_to_big_endian(byte);
	i = ft_strlen(header->file_name) - 1;
	while (--i > 0 && header->file_name[i] != '.')
	{
		;
	}
	if (!i)
		header->file_name = ".cor";
	else
		ft_strcpy(&header->file_name[i], ".cor");
	fd = open(header->file_name, O_CREAT | O_RDWR, 0644);
	write(fd, &byte, 4);
	write(fd, header->name, PROG_NAME_LENGTH);
	byte = 0;
	write(fd, &byte, 4);
	length = convert_to_big_endian(length);
	write(fd, &length, 4);
	write(fd, header->comment, COMMENT_LENGTH);
	write(fd, &byte, 4);
	write_program(header, fd);
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
	
	prog->file_name = argv[1];
	if (!program_parser(prog, data))
	{
		if (!prog->i)
			return (printf("Syntax error at token [TOKEN][%0.3d:%0.3d] END \"(null)\"\n", 
				prog->nb_line, prog->i));
		else if (prog->debug)
			print_debug(prog);
		else
		{
			magic_number(prog);
			printf("Writing output program to %s\n", prog->file_name);
		}
	}
	return (0);
}
