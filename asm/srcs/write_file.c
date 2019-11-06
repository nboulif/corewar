/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 14:39:04 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/06 15:01:22 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	size_t	convert_to_big_endian(size_t x, int dir_size)
{
	if (!dir_size)
		return (((x >> 24) & 0x000000ff) | ((x >> 8) & 0x0000ff00) |
			((x << 8) & 0x00ff0000) | ((x << 24) & 0xff000000));
	else
		return ((((x >> 8) & 0x00ff) |
				((x << 8) & 0xff00)));
}

static int		write_program(t_data *data, int fd)
{
	int		i;
	int		size;
	size_t	byte;

	while (data && (i = -1))
	{
		if (!data->op)
		{
			data = data->next;
			continue;
		}
		write(fd, &data->op->opc, 1);
		if (data->codage_octal != 128)
			write(fd, &data->codage_octal, 1);
		while (++i < 3)
		{
			size = (data->codage_octal >> (2 * (3 - i))) & 3;
			if (size == 2 && !data->op->dir_size && (size = 4))
				byte = convert_to_big_endian(data->val_param[i], 0);
			else if ((size == 2 || size == 3) && (size = 2))
				byte = convert_to_big_endian(data->val_param[i], 1);
			else
				byte = data->val_param[i];
			write(fd, &byte, size);
		}
		data = data->next;
	}
	return (0);
}

static int		get_output_file_name(t_prog *prog)
{
	int	i;

	i = ft_strlen(prog->file_name) - 1;
	while (i >= 0 && prog->file_name[i] != '.')
		i--;
	if (!i)
		prog->file_name = ".cor";
	else
		ft_strcpy(&prog->file_name[i], ".cor");
	return (0);
}

/*
** write_header:
** 	- magic number
** 	- program name
** 	- 4 bytes 0
** 	- program length
** 	- program comment
**	- 4 bytes 0
*/

int				write_header(t_prog *prog, int fd)
{
	size_t	byte;

	byte = convert_to_big_endian(COREWAR_EXEC_MAGIC, 0);
	write(fd, &byte, 4);
	write(fd, prog->name, PROG_NAME_LENGTH);
	byte = 0;
	write(fd, &byte, 4);
	byte = convert_to_big_endian(prog->prog_size, 0);
	write(fd, &byte, 4);
	write(fd, prog->comment, COMMENT_LENGTH);
	byte = 0;
	write(fd, &byte, 4);
	return (0);
}

int				write_file(t_prog *prog)
{
	int		fd;

	get_output_file_name(prog);
	printf("Writing output program to %s\n", prog->file_name);
	fd = open(prog->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	write_header(prog, fd);
	write_program(prog->list_data, fd);
	close(fd);
	return (0);
}
