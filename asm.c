#include <unistd.h>
#include <fcntl.h>
#include "op.h"
#include <stdio.h>

unsigned int ConvertToBigEndian(unsigned int x)
{
	return (((x>>24) & 0x000000ff) | ((x>>8) & 0x0000ff00) | ((x<<8) & 0x00ff0000) | ((x<<24) & 0xff000000));
}

int magic_number(t_prog *header)
{
	int fd;
	unsigned int byte = COREWAR_EXEC_MAGIC;

	byte = ConvertToBigEndian(byte);
	fd = open(header->name, O_CREAT | O_RDWR, 0644);
	write(fd, &byte, 4);
	write(fd, header->name, 128);
	write(fd, header->comment, 2048);
	close(fd);
	return (0);
}
