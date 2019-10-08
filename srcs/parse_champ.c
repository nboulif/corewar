#include "vm_corewar.h"

void	print_error_and_exit(int type_of_error)
{
	char *str[6] = {"READ ERROR\n", "BAD MAGIC NUMBER\n",\
					"INDEX DOUBLON\n", "TOO MUCH CHAMPS\n",\
					"MALLOC ERROR\n", "OPEN FAILED\n"};

	ft_putstr_fd(str[-type_of_error - 1], 2);
	exit(1);
}

int		strcpy_champ(char *dest, char *src, int size)
{
	int i = 0;

	while (src[i])
	{
		dest[i] = src[i];
		if (++i > size)
			return (0);
	}
	dest[i] = 0;
	return (i);
}

int		init_champ_header(t_champs *champ, char	*mem, char *index)
{
	int i;
	int	offset;

	if (!(champ->name = malloc(sizeof(char) * PROG_NAME_LENGTH)) ||
		!(champ->comment = malloc(sizeof(char) * COMMENT_LENGTH)))
		return (0);
	champ->size_name = strcpy_champ(champ->name, mem, PROG_NAME_LENGTH);
	champ->size_comment = strcpy_champ(champ->name,
		&mem[PROG_NAME_LENGTH + NULL_SIZE], COMMENT_LENGTH);
	champ->index = atoi(index);
	return (1);
}

int		check_index_doublon(t_all *all, int index)
{
	int i;

	i = 0;
	while (i < index)
		if (all->champ[i].index == all->champ[index].index)
			return (0);
	return (1);
}

int		parse_champ(t_all *all, char *index, char *file)
{
	int			fd;
	char		mem[FULL_HEADER_COR_SIZE];
	static int	champ_count = -1;

	if (++champ_count == 3)
		return (TOO_MUCH_CHAMPS);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (OPEN_ERROR);
	if (read(fd, mem, FULL_HEADER_COR_SIZE) < FULL_HEADER_COR_SIZE)
		return (READ_ERROR);
	if (*((int*)mem) != COREWAR_EXEC_MAGIC)
		return (BAD_MAGIC_NUMBER);
	if (!init_champ_header(&all->champ[champ_count],
			&mem[MAGIC_SIZE], index))
		return (MALLOC_ERROR);
	if (!check_index_doublon(all, champ_count))
		return (INDEX_DOUBLON);
	close(fd);
	return (1);
}

// int		main()
// {
// 	char mem[4] = {'1','2','3','4'};

// 	printf("|%d| - |%d|\n", (int)mem[3] << 24 | (int)mem[2] << 16 |(int)mem[1] << 8 | (int)mem[0], ((int*)mem)[0]);
// 	return (0);
// }