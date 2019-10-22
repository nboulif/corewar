#include "vm_corewar.h"

int		strcpy_champ(char *dest, char *src, int size)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		if (++i > size)
			return (0);
	}
	dest[i] = 0;
	return (i);
}

int		init_champ_header(t_champ *champ, char	*mem, char *index)
{
	if (!(champ->name = malloc(sizeof(char) * (PROG_NAME_LENGTH + 1))) ||
		!(champ->comment = malloc(sizeof(char) * (COMMENT_LENGTH + 1))))
		return (0);
	champ->size_name = strcpy_champ(champ->name, mem, PROG_NAME_LENGTH);
	champ->size_comment = strcpy_champ(champ->comment,
		&mem[PROG_NAME_LENGTH + NULL_SIZE + EXEC_SIZE], COMMENT_LENGTH);
	return (1);
}

int		check_index_doublon(t_all *all, int index)
{
	int i;

	i = -1;
	while (++i < index)
		if (all->champ[i].flag_index && all->champ[i].index == all->champ[index].index)
			return (0);
	return (1);
}

int		check_index(char *index)
{
	int i;

	i = 0;
	if (index[i] == '-' || index[i] == '+')
		i++;
	while (index[i])
		if (!ft_isdigit(index[i++]))
			return (0);
	return (1);
}

void	fix_index(t_champ *champ, char *index)
{
	int		index_int;

	if (!index || check_index(index))
		return ;
	index_int = ft_atoi(index);
	if (index_int < -124 || index_int > 123)
		return ;
	champ->flag_index = 1;
	champ->index = (char)index_int;
}

int		parse_champ(t_all *all, char *index, char *file)
{
	static int	champ_count = -1;
	char		mem[FULL_HEADER_COR_SIZE];
	int			fd;
	int			mem_nbr;

	if (++champ_count == 4)
		print_error_and_exit(TOO_MANY_CHAMP);
	fix_index(&all->champ[champ_count], index);
	printf("file to open |%s|\n", file);
	if ((fd = open(file, O_RDONLY)) == -1)
		print_error_and_exit(OPEN_ERROR);
	if (read(fd, mem, FULL_HEADER_COR_SIZE) < FULL_HEADER_COR_SIZE ||
		!(all->champ[champ_count].size_exec =
		read_all((char**)&all->champ[champ_count].exec_code, fd)))
		print_error_and_exit(READ_ERROR);
	if (*((int*)mem) != ((COREWAR_EXEC_MAGIC & 0xff) << 24 |
						(COREWAR_EXEC_MAGIC & 0xff0000) >> 8 |
						(COREWAR_EXEC_MAGIC & 0xff00) << 8))
		print_error_and_exit(BAD_MAGIC_NUMBER);
	if (!init_champ_header(&all->champ[champ_count],
			&mem[MAGIC_SIZE], index))
		print_error_and_exit(MALLOC_ERROR);
	if (!check_index_doublon(all, champ_count))
		print_error_and_exit(INDEX_DOUBLON);
	printf("name -> |%s|\n", all->champ[champ_count].name);
	printf("comment -> |%s|\n",all->champ[champ_count].comment);
	mem_nbr = *(int*)&mem[MAGIC_SIZE + PROG_NAME_LENGTH + NULL_SIZE];
	mem_nbr = (mem_nbr & 0xff) << 24 | (mem_nbr & 0xff0000) >> 8 | (mem_nbr & 0xff00) << 8 | (mem_nbr & 0xff000000) >> 24;
	if (all->champ[champ_count].size_exec != mem_nbr)
		print_error_and_exit(EXEC_SIZE_ERROR);
	close(fd);
	return (1);
}

// int		main()
// {
// 	char mem[4] = {'1','2','3','4'};

// 	printf("|%d| - |%d|\n", (int)mem[3] << 24 | (int)mem[2] << 16 |(int)mem[1] << 8 | (int)mem[0], ((int*)mem)[0]);
// 	return (0);
// }