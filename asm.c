/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:10:31 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/14 15:11:23 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "asm.h" 
#include "op.h"
#include "libft/libft.h"

unsigned int ConvertToBigEndian(unsigned int x)
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
	byte = ConvertToBigEndian(byte);
	fd = open(header->name, O_CREAT | O_RDWR, 0644);
	write(fd, &byte, 4);
	write(fd, header->name, PROG_NAME_LENGTH);
	byte = 0;
	write(fd, &byte, 4);
	length = ConvertToBigEndian(length);
	write(fd, &length, 4);
	write(fd, header->comment, COMMENT_LENGTH);
	write(fd, &byte, 4);
	close(fd);
	return (0);
}
