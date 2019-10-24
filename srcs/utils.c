#include "vm_corewar.h"

char *text_color[256] = {"\033[0m", "\033[0;31m", "\033[0;32m", "\033[0;33m","\033[0;34m", "\033[0;35m"}; //Set the text to the color red

void moveUp(int positions) {
 	printf("\x1b[%dA", positions);
  }
  
 void moveDown(int positions) {
	printf("\x1b[%dB", positions);
}

 void moveRight(int positions) {	
	printf("\x1b[%dC", positions);
}

 void moveLeft(int positions) {	
	printf("\x1b[%dD", positions);
}

 void moveTo(int row, int col) {
 	printf("\x1b[%d;%df", row, col); }

void	print_bit(char nb)
{
	int i;

	i = 1;
	printf("print_bit->:\n");
	for (int x = 0; x < 7; x++)
	{
		printf("%d", !!(nb & (i << x)));
	}
	printf("\n");
}

int		is_a_process(t_all *all, int pc)
{
	int			i;
	t_process	*proc;

	i = -1;
	while (++i < all->stack_proc->n_items)
	{
		proc = (t_process*)ft_array_get(all->stack_proc, i);
		if (pc == proc->pc)
		{
			return ((unsigned int)proc->origin_champ->index % 4 + 1);
		}
	}
	return (0);
}

void					hexdump_map_square(t_all *all)
{
	int i;

	i = -1;
	moveTo(0, 0);
	while (++i < MEM_SIZE)
	{
		printf("%s", text_color[is_a_process(all, i)]);
		if (!((i + 1) % 64))
			printf("%.2hhx\n", all->map[i]);
		else
			printf("%.2hhx ", all->map[i]);
	}
	// printf("\n");
	read(0, &i, 4);
}

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
	char *str[9] = {"READ ERROR\n", "BAD MAGIC NUMBER\n",\
					"INDEX DOUBLON\n", "TOO MUCH CHAMPS\n",\
					"MALLOC ERROR\n", "OPEN FAILED\n",\
					"INCOMPLETE ARGUMENT\n", "BAD EXEC_SIZE\n",\
					"INVALID CYCLE AMOUNT (DUMP)\n"};

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

int		rev_int_byte(int nbr)
{
	return ((nbr & 0xff) << 24 | (nbr & 0xff0000) >> 8 |
		(nbr & 0xff00) << 8 | (nbr & 0xff000000) >> 24);
}

void		move_pc(int *pc, int incr)
{
	if (incr >= MEM_SIZE || incr <= -MEM_SIZE)
		incr %= MEM_SIZE;
	if (incr < 0)
	{
		if ((*pc += incr) < 0)
			*pc = MEM_SIZE - *pc;
	}
	else
		*pc = (*pc + incr) % MEM_SIZE;
}

t_champ		*get_champ(int index, t_all *all)
{
	int		i;

	i = -1;
	while (++i < all->nb_champ)
	{
		if (all->champ[i].index == index)
			return (&all->champ[i]);
	}
	return (NULL);
}