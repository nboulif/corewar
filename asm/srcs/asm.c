/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op 			*check_if_operation(char *line)
{
	int i;

	i = -1;
	while (++i < 16)
		if (!ft_strcmp(line, g_op_tab[i].name))
			return (&g_op_tab[i]);
	return (NULL);
	
}


void 	write_header(t_asm *u)
{
	int 		byte;

	byte = COREWAR_EXEC_MAGIC >> 24;
	write(u->fd_output, &byte, 1);
	byte = COREWAR_EXEC_MAGIC >> 16;
	write(u->fd_output, &byte, 1);
	byte = COREWAR_EXEC_MAGIC >> 8;
	write(u->fd_output, &byte, 1);
	byte = COREWAR_EXEC_MAGIC;
	write(u->fd_output, &byte, 1);

	write(u->fd_output, u->prog->prog_name, PROG_NAME_LENGTH);

	byte = 0;
	write(u->fd_output, &byte, 4);
	byte = 0;
	write(u->fd_output, &byte, 1);
	write(u->fd_output, &byte, 1);
	byte = u->prog->prog_size >> 8;
	write(u->fd_output, &byte, 1);
	byte = u->prog->prog_size;
	write(u->fd_output, &byte, 1);

	write(u->fd_output, u->prog->comment, COMMENT_LENGTH);
	byte = 0;
	write(u->fd_output, &byte, 4);
}

void 	write_program(t_asm *u)
{
	t_inst		*cur_inst;
	t_op_ch		*cur_op_ch;
	int			i;

	write_header(u);
	
	cur_inst = u->prog->insts;
	while (cur_inst)
	{
		ft_putendl("---INSTRUCTION---");
		ft_putnbr(cur_inst->index);
		ft_putstr("  ");
		ft_putendl(cur_inst->name);
		
		cur_op_ch = cur_inst->ops;

		while (cur_op_ch)
		{
			ft_putendl("---OPERATION---");
			ft_putnbr(cur_op_ch->index);
			ft_putstr("  ");
			ft_putendl(cur_op_ch->op->name);

			write(u->fd_output, &cur_op_ch->op->op_code, 1);
			if (cur_op_ch->op->codage_octal)
				write(u->fd_output, &cur_op_ch->param_codage, 1);
			
			i = -1;
			ft_putendl("---PARAMS---");
			while (cur_op_ch->params[++i])
			{
				cur_op_ch->params[i] = zap_space_tab(cur_op_ch->params[i]);

				if (cur_op_ch->params[i][0] == 'r')
				{
					handle_register(u, &cur_op_ch->params[i][1]);
				}
				else if(ft_isdigit(cur_op_ch->params[i][0]) || cur_op_ch->params[i][0] == '-')
				{
					handle_number(u, &cur_op_ch->params[i][0]);
				}
				else if (cur_op_ch->params[i][0] == DIRECT_CHAR)
				{
					handle_direct(u, &cur_op_ch->params[i][1], cur_op_ch);
				}
				else
				{
					ft_putendl("------------");
					ft_putendl("error 856");
					ft_putendl("------------");
				}

				ft_putendl(cur_op_ch->params[i]);
			}
			// ft_tabdel(&cur_op_ch->params);

			
			cur_op_ch = cur_op_ch->next;
		}
		cur_inst = cur_inst->next;
	}
}

t_asm		*init_asm(void)
{
	t_asm		*u;

	u = (t_asm*)malloc(sizeof(t_asm));

	u->magic = COREWAR_EXEC_MAGIC;
	u->octal_index = 0;
	
	u->prog = (t_prog*)malloc(sizeof(t_prog));

	u->prog->extend = 0;
	u->prog->insts = (t_inst*)malloc(sizeof(t_inst));
	u->prog->insts->name = ft_strdup("main");
	u->prog->insts->index = u->octal_index;
	u->prog->insts->address = 0;
	u->prog->insts->ops = NULL;
	u->prog->insts->prev = NULL;
	u->prog->insts->next = NULL;
	
	return (u);
}

int main_asm(int argc, char const *argv[])
{
	t_asm		*u;
	char 		*output_name;
	
	if (argc != 2)
	{
		ft_putendl("WRONG NB PARAM");
		return (0);
	}

	if (!(u = init_asm()))
	{
		ft_putendl("ERROR MALLOC U");
		return (0);
	}
	
	if ((u->fd_input = open(argv[1], O_RDONLY)) < 0)
	{
		ft_putendl("ERROR OPEN FILE");
		return (0);
	}

	output_name = strdup(argv[1]);
	output_name[ft_strlen(output_name) - 1] = 'c';
	output_name = ft_strjoin(output_name , "or");
	
	if ((u->fd_output = open(output_name, O_CREAT | O_RDWR, 0644)) < 0)
	{
		ft_putendl("ERROR CREATE/OPEN OUT FILE");
		return (0);
	}

	parse_file(u);

	u->prog->prog_size = u->octal_index;

	write_program(u);
	
	return (0);
}

int		main(int argc, char const *argv[])
{

	return (main_asm(argc, argv));

}

