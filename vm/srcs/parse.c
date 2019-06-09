/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int parse_param(uint32_t codage_octal, int id, t_op *op, uint32_t *index)
{
	int argv;

	argv = 0;
	if (codage_octal == REG_CODE)
	{
		argv = u_vm->champions[id]->prog->prog[(*index)++];
	}
	else if (codage_octal == DIR_CODE)
	{
		if (!op->dir_size)
		{
			argv =  (argv | u_vm->champions[id]->prog->prog[(*index)++]) << 8;
			argv =  (argv | u_vm->champions[id]->prog->prog[(*index)++]) << 8;
			argv =  (argv | u_vm->champions[id]->prog->prog[(*index)++]) << 8;
			argv =  (argv | u_vm->champions[id]->prog->prog[(*index)++]);
		}
		else
		{
			argv |=  u_vm->champions[id]->prog->prog[(*index)++] << 8;
			argv |=  u_vm->champions[id]->prog->prog[(*index)++];
			argv = (short)argv;
		}
	}
	else if (codage_octal == IND_CODE)
	{
		argv |=  u_vm->champions[id]->prog->prog[(*index)++] << 8;
		argv |=  u_vm->champions[id]->prog->prog[(*index)++];
		argv = (short)argv;

	}
	return (argv);
}

int		parse_champion_file(int id)
{
	uint32_t		index;
	t_op				*op;
	uint8_t 		codage_octal;
	index = 0;
	while (index < u_vm->champions[id]->prog->prog_size)
	{
		ft_putnbr(index);
		if (!(op = check_if_operation(u_vm->champions[id]->prog->prog[index++])))
		{	
			ft_putendl("ERROR NOT OPERATION CODE");
			return (0);
		}
		ft_putstr("       ");
		ft_putendl(op->name);
		int argc;
		int i;
		argc = op->argc;
		ft_putnbr(op->op_code);
		ft_putstr("       ");
		if (op->codage_octal)
		{				
			codage_octal = u_vm->champions[id]->prog->prog[index++];
			i = 6;
			ft_putnbr(codage_octal);
			ft_putstr("       ");
		}
		else
		{
			codage_octal = op->argv[0];
			i = 0;
		}
		while (argc--)
		{
			ft_putnbr(parse_param(((codage_octal >> i) & 3), id, op, &index));
			if (argc)
				ft_putstr("       ");
			i -= 2;
		}
		ft_putstr("\n\n");
	}

	return (1);
}

int		check_valid_magic(void)
{
	uint8_t		buff[4];
	int					res;

	if ((res = read(u_vm->fd_input, buff, 4)) == 4 
		&& buff[0] == 0 && buff[1] == 234 
		&& buff[2] == 131 && buff[3] == 243)
	{
		return (1);
	}
	ft_putendl("ERROR : WRONG MAGIC");
	return (0);
}

int		parse_champion_header(int id)
{
	int				res;
	char			buff[COMMENT_LENGTH + 1];
	uint32_t	prog_size;

	if (!check_valid_magic())
		return (0);
	
	res = read(u_vm->fd_input, buff, PROG_NAME_LENGTH);
	ft_memcpy(u_vm->champions[id]->prog->prog_name, buff, PROG_NAME_LENGTH);
	u_vm->champions[id]->prog->prog_name[PROG_NAME_LENGTH] = '\0';
	res = read(u_vm->fd_input, buff, 4); // NULL
	// ft_putendl(u_vm->champions[id]->prog->prog_name);
	res = read(u_vm->fd_input, buff, 4);

	prog_size = 0;
	prog_size =  (prog_size | buff[0]) << 8;
	prog_size =  (prog_size | buff[1]) << 8;
	prog_size =  (prog_size | buff[2]) << 8;
	prog_size =  (prog_size | buff[3]);
	u_vm->champions[id]->prog->prog_size = prog_size;
	// ft_putnbr(u_vm->champions[id]->prog->prog_size);
	// ft_putendl(" ");

	res = read(u_vm->fd_input, buff, COMMENT_LENGTH);
	ft_memcpy(u_vm->champions[id]->prog->comment, buff, COMMENT_LENGTH);
	u_vm->champions[id]->prog->comment[COMMENT_LENGTH] = '\0';
	// ft_putendl(u_vm->champions[id]->prog->comment);
	res = read(u_vm->fd_input, buff, 4); // NULL
	
	return (1);
}

int		parse_champion_prog(int id)
{
	uint8_t		*buff;
	int			res;

	buff = (uint8_t*)malloc(sizeof(uint8_t) *
		u_vm->champions[id]->prog->prog_size);

	res = read(u_vm->fd_input, buff, u_vm->champions[id]->prog->prog_size);

	u_vm->champions[id]->prog->prog = buff;

	return (1);
}

int		parse_champion(int id, char *argv)
{

	if ((u_vm->fd_input = open(argv, O_RDONLY)) < 0)
	{

		ft_putendl("ERROR OPEN IN FILE");
		return (0);
	}
	u_vm->champions[id] = (t_champion*)malloc(sizeof(t_champion));

	u_vm->champions[id]->prog = (t_prog*)malloc(sizeof(t_prog));
	parse_champion_header(id);
	parse_champion_prog(id);

	close(u_vm->fd_input);
	return (1);
}

int		parse_champions(int argc, char *argv[])
{
	int i;

	u_vm->champions = (t_champion**)malloc(sizeof(t_champion*) * MAX_PLAYERS);

	i = 0;
	while (++i < argc)
	{
		if (!parse_champion(i - 1, argv[i]))
		{
			ft_putendl("ERROR PARSE CHAMPION");
			return (0);
		}
		u_vm->nb_champion = i;
	}
	return (1);
}
