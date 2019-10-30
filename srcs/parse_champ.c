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

void	fix_index(t_champ *champ, char *index)
{
	int		index_int;

	if (!index || !check_index(index))
		return ;
	index_int = ft_atoi(index);
	if (index_int < INT_MIN + 3)
		return ;
	champ->flag_index = 1;
	champ->index = (char)index_int;
}

void		parse_champ(t_all *all, char *index, char *file)
{
	char		mem[FULL_HEADER_COR_SIZE];
	int			fd;

	if (++all->nb_champ == 5)
		print_error_and_exit(TOO_MANY_CHAMP);
	fix_index(&all->champ[all->nb_champ - 1], index);
	if ((fd = open(file, O_RDONLY)) == -1)
		print_error_and_exit(OPEN_ERROR);
	if (read(fd, mem, FULL_HEADER_COR_SIZE) < FULL_HEADER_COR_SIZE ||
		!(all->champ[all->nb_champ - 1].size_exec =
		read_all((char**)&all->champ[all->nb_champ - 1].exec_code, fd)))
		print_error_and_exit(READ_ERROR);
	if (*((int*)mem) != COREWAR_EXEC_MAGIC_REV)
		print_error_and_exit(BAD_MAGIC_NUMBER);
	if (!init_champ_header(&all->champ[all->nb_champ - 1],
			&mem[MAGIC_SIZE], index))
		print_error_and_exit(MALLOC_ERROR);
	if (!check_index_doublon(all, all->nb_champ - 1))
		print_error_and_exit(INDEX_DOUBLON);
	if (all->champ[all->nb_champ - 1].size_exec !=
		rev_int_byte(*(int*)&mem[MAGIC_SIZE + PROG_NAME_LENGTH + NULL_SIZE]) ||
		all->champ[all->nb_champ - 1].size_exec > CHAMP_MAX_SIZE)
		print_error_and_exit(EXEC_SIZE_ERROR);
	close(fd);
}
