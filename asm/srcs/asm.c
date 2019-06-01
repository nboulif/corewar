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


void 	write_program(t_asm *u)
{
	t_inst		*cur_inst;
	t_op_ch		*cur_op_ch;
	int			i;
	int 		byte;


	cur_inst = u->insts;
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
					byte = 254;
					write(u->fd_output, &byte, 1);
				}

				// ft_putnbr(cur_op_ch->index);
				// ft_putstr("  ");

				ft_putendl(cur_op_ch->params[i]);
			}

			
			cur_op_ch = cur_op_ch->next;
		}
		cur_inst = cur_inst->next;
	}
}

int		main(int argc, char const *argv[])
{
	t_asm		*u;
	
	if (argc != 2)
	{
		ft_putendl("WRONG NB PARAM");
		return (0);
	}

	u = (t_asm*)malloc(sizeof(t_asm));
	u->fd_input = open(argv[1], O_RDONLY);
	u->extend = 0;
	u->octal_index = 0;

	u->insts = (t_inst*)malloc(sizeof(t_inst));
	u->insts->name = ft_strdup("main");
	u->insts->index = u->octal_index;
	u->insts->address = 0;
	u->insts->ops = NULL;
	u->insts->prev = NULL;
	u->insts->next = NULL;
	
	if (u->fd_input <= 0)
	{
		ft_putendl("ERROR OPEN FILE");
		return (0);
	}

	if ((u->fd_output = open("test_2.cor", O_CREAT | O_RDWR, 0644)) < 0)
	{
		return (0);
	}
	parse_file(u);
	write_program(u);
	return (0);
}

