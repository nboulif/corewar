/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		run_vm()
{

	return (1);
}

int		init_vm()
{

	return (1);
}

t_op 			*check_if_operation(unsigned char octet)
{
	int i;

	i = -1;
	while (++i < 16)
		if (g_op_tab[i].op_code == octet)
			return (&g_op_tab[i]);
	return (NULL);
	
}

int		parse_player(int id)
{
	// u_vm->players = realloc(u_vm->players, id * sizeof(t_player));
	char *buff;
	int 	index;

	buff = (char*)malloc(sizeof(char) * 8);
	int res;

	res = read(u_vm->fd_input, buff, 4 + PROG_NAME_LENGTH + 4 + 4 + COMMENT_LENGTH + 4);
	
	
	t_op 	*op;

	index = 0;
	while (read(u_vm->fd_input, buff, 1) > 0)
	{
		if (!(op = check_if_operation(buff[0])))
		{
			
			ft_putendl("ERROR NOT OPERATION CODE");
			return (0);
		}
		else
		{
			ft_putnbr(index);
			ft_putstr("____");
			ft_putendl(op->name);
			
			index++;

			int size_to_read;
			
			size_to_read = 0;

			if (op->codage_octal)
			{
				res = read(u_vm->fd_input, buff, 1);
				index++;

				unsigned char oo = buff[0];
				unsigned char ooo;


				int i;
				i = 7;
				while (i >= 0)
				{
					unsigned char o = (oo >> i) & 1;
					ft_putnbr(o);
					i--;
				}
				ft_putendl(" ");
				

				unsigned int y;

				y = 0;
				i = 6;
				while (y++ < op->argc)
				{

					ooo = (oo >> i) & 3;
					ft_putnbr(ooo);
					ft_putstr(" ----- ");
					if (ooo)
					{
						if (ooo == IND_CODE)
							size_to_read = 2;
						else if (ooo == DIR_CODE)
							size_to_read = op->dir_size ? 2 : 4;
						else if (ooo == REG_CODE)
						{
							size_to_read = 1;
						}
						ft_putnbr(size_to_read);
						read(u_vm->fd_input, buff, size_to_read);
						if (ooo == REG_CODE)
						{
							ft_putstr(" ----- ");
							ft_putnbr(buff[0]);
						}
						else if (ooo == DIR_CODE)
						{
							unsigned int ppp;

							ppp = 0;
							if (size_to_read == 4)
							{
								ppp =  (ppp | buff[0]) << 8;
								ppp =  (ppp | buff[1]) << 8;
								ppp =  (ppp | buff[2]) << 8;
								ppp =  (ppp | buff[3]);
							}
							else
							{
								ppp |=  buff[0] << 8;
								ppp |=  buff[1];
							}
							ft_putstr(" ----- ");
							ft_putnbr(ppp);
						}
						else if (ooo == IND_CODE)
						{
							unsigned int ppp;

							ppp = 0;
							ppp |=  buff[0] << 8;
							ppp |=  buff[1];

							ft_putstr(" ----- ");
							ft_putnbr(ppp);
						}
					}
					else
					{
						ft_putendl("ERROR WRONG CODAGE OCTAL");
						return (0);
					}
					index += size_to_read;
					ft_putendl(" ");
					i -= 2;
				}
			}
			else
			{
				if (!ft_strcmp("live", op->name))
					size_to_read = 4;
				else if (!ft_strcmp("zjmp", op->name))
					size_to_read = IND_SIZE;
				else if (!ft_strcmp("fork", op->name))
					size_to_read = op->dir_size ? 2 : 4;
				else if (!ft_strcmp("lfork", op->name))
					size_to_read = op->dir_size ? 2 : 4;
				read(u_vm->fd_input, buff, size_to_read);
				
				index += size_to_read;
				
			}
			ft_putendl(" ");
		}
		// break;
		
		// res = read(u_vm->fd_input, buff, 8);
		// printf("%.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x", 
		// 	buff[0], buff[1], buff[2], buff[3],
		// 	buff[4], buff[5], buff[6], buff[7]);
		// res = read(u_vm->fd_input, buff, 8);
		// printf("  %.2x %.2x %.2x %.2x %.2x %.2x %.2x %.2x\n", 
		// 	buff[0], buff[1], buff[2], buff[3],
		// 	buff[4], buff[5], buff[6], buff[7]);
	}


	u_vm->nb_player = id;

	return (1);
}

int		parse_champion(int id, char *argv)
{

	if ((u_vm->fd_input = open(argv, O_RDONLY)) < 0)
	{

		ft_putendl("ERROR OPEN IN FILE");
		return (0);
	}

	if (!parse_player(id))
	{
		ft_putendl("ERROR PARSE");
		return (0);
	}

	close(u_vm->fd_input);
	return (1);
}

int		parse_champions(int argc, char *argv[])
{
	int i;

	i = 0;
	while (++i < argc)
	{
		if (!parse_champion(i, argv[i]))
		{
			ft_putendl("ERROR PARSE CHAMPION");
			return (0);
		}
		
	}
	return (1);
}

int		main(int argc, char *argv[])
{	
	if (argc < 2)
	{
		ft_putendl("WRONG NB PARAM");
		return (0);
	}

	u_vm = (t_vm*)malloc(sizeof(t_vm));
	
	u_vm->magic = COREWAR_EXEC_MAGIC;

	parse_champions(argc, argv);
	
	return (run_vm());
}
