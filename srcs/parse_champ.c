#include "../includes/vm.h"

int		parse_champ(t_all *all, char *index, char *file)
{
	int fd;

	if ((fd = open(file)) == -1)
		return (0);
	
	close(fd);
	return (1);
}