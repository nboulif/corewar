#include "vm_corewar.h"

unsigned int		flags[256] = {0};
char				*flags_syn[256] = {NULL};

void				config_flags(void)
{
	flags['d'] = FLAG_DUMP;
	flags['n'] = FLAG_NUMBER;
	flags['t'] = FLAG_THREAD;
	flags['v'] = FLAG_VISU;
}

void				config_flags_syn(void)
{
	flags_syn['d'] = "dump";
}

int				ft_realloc(void **tab, int *size_av,
		int new_size_ap, size_t type_size)
{
	char			*save;
	unsigned int	size;
	unsigned int	new_size;

	size = *size_av;
	new_size = new_size_ap;
	if (new_size == size)
		return (1);
	if (!(save = malloc(new_size * type_size)))
		return (0);
	if (size)
	{
		ft_memcpy(save, *tab, size * type_size);
		free(*tab);
	}
	*tab = save;
	if (new_size > size)
		ft_memset(*tab + size, 0, (new_size - size) * type_size);
	*size_av = new_size;
	return (1);
}

int			read_all(char **str, int fd)
{
	int index;
	int size;
	int ret;

	size = SIZE_BUFF + 1;
	if (!(*str = malloc(size * sizeof(char))))
		print_error_and_exit(MALLOC_ERROR);	
	index = 0;
	while ((ret = read(fd, *str + index, SIZE_BUFF)) > 0)
	{
		index += ret;
		(*str)[index] = 0;
		if (ret < SIZE_BUFF)
			return (index);
		if (index + SIZE_BUFF >= size - 1)
			if (!ft_realloc((void **)str, &size, size * 2, sizeof(char)))
				print_error_and_exit(MALLOC_ERROR);
	}
	if (ret < 0)
		print_error_and_exit(READ_ERROR);
	return (index);
}

void	print_error_and_exit(int type_of_error)
{
	char *str[8] = {"READ ERROR\n", "BAD MAGIC NUMBER\n",\
					"INDEX DOUBLON\n", "TOO MUCH CHAMPS\n",\
					"MALLOC ERROR\n", "OPEN FAILED\n",\
					"INCOMPLETE CHAMP SPECIFICATION\n", "BAD EXEC_SIZE\n"};

	ft_putstr_fd(str[-type_of_error - 1], 2);
	exit(1);
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