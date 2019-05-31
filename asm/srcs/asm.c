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

t_op_ch			*define_operation(t_inst *cur_inst, t_op_ch *cur_op_ch, t_op *op)
{


	if (!op)
	{
		ft_putendl("---NOT OPERATION---");
		return (NULL);
	}
	if (!cur_op_ch)
	{
		cur_op_ch = (t_op_ch*)malloc(sizeof(t_op_ch));
		cur_op_ch->op = op;
		cur_op_ch->prev = NULL;
		cur_op_ch->next = NULL;
		cur_op_ch->index = 0;

		cur_inst->ops = cur_op_ch;
		return (cur_op_ch);
	}
	else
	{
		cur_op_ch->next = (t_op_ch*)malloc(sizeof(t_op_ch));
		cur_op_ch->next->op = op;
		cur_op_ch->next->prev = cur_op_ch;
		cur_op_ch->next->next = NULL;
		cur_op_ch->next->index = cur_op_ch->index + 1;

		return (cur_op_ch->next);
	}
}

t_inst *		define_instruction(t_asm *u, t_inst *cur_inst, char *word)
{

	if (!ft_strcmp(cur_inst->name, "main") && !cur_inst->ops)
	{
		ft_strdel(&cur_inst->name);
		cur_inst->name = ft_strdup(word);
		cur_inst->index = u->octal_index;
		return (cur_inst);
	}
	else
	{
		cur_inst->next = (t_inst*)malloc(sizeof(t_inst));
		cur_inst->next->name = ft_strdup(word);
		cur_inst->next->index = u->octal_index;
		cur_inst->next->address = 0;
		cur_inst->next->ops = NULL;
		cur_inst->next->prev = cur_inst;
		cur_inst->next->next = NULL;

		return (cur_inst->next);
	}
}

char	*zap_space_tab(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (line);
}

char	*retrieve_next_world(char **line)
{
	char		*word;
	int			i;
	
	i = 0;
	(*line) = zap_space_tab(*line);

	while (*((*line) + i))
	{
		if (!ft_strchr(LABEL_CHARS, *((*line) + i)))
			break ;
		i++;
	}
	
	if (i == 0)
		return (NULL);
	word = ft_strsub((*line), 0, i);
	(*line) += i; 
	return (word);

}


int		check_line(t_asm *u, t_inst *cur_inst, t_op_ch *cur_op_ch, char *line)
{
	t_op		*op;
	char		*word;
	int			res;
	char		*line_o;

	res = get_next_line(u->fd_input, &line);
	if (res <= 0)
		return (res);
	line_o = line;	
	if (*line == '#')
		return (check_line(u, cur_inst, cur_op_ch, line));
	if (!(word = retrieve_next_world(&line)))
		return (check_line(u, cur_inst, cur_op_ch, line));

	op = check_if_operation(word);
	
	if ((!op || !ft_strcmp("live", word)) && (*line == LABEL_CHAR || !ft_strcmp("main", cur_inst->name)))
	{
		line++;
		if (!(cur_inst = define_instruction(u, cur_inst, word)))
			return (0);
		
		cur_op_ch = NULL;
		if (!(word = retrieve_next_world(&line)))
			return (check_line(u, cur_inst, NULL, line));
		op = check_if_operation(word);
	}

	if (!(cur_op_ch = define_operation(cur_inst, cur_op_ch, op)))
		return (-1);

	// u->octal_index;	

	line = zap_space_tab(line);
	cur_op_ch->params = ft_strsplit(line, ',');

	if (!cur_op_ch->params)
		return(-1);	
	
	// ft_tabdel(&line_splited);

	ft_strdel(&line_o);

	return (check_line(u, cur_inst, cur_op_ch, line));
}


int		parse_header(t_asm *u, char **line)
{
	int 		res;

	
	while ((res = get_next_line(u->fd_input, &(*line))) == 1)
	{
		if ((*line)[0] == '#')
		{

			ft_strdel(&(*line));
			continue;
		}
		else if (ft_strstr((*line), ".name"))
			u->name = *line;
		else if (ft_strstr((*line), ".comment"))
			u->comment = *line;
		else if (ft_strstr((*line), ".extend"))
			u->extend = 1;
		else
			break ;
	}

	return (res);

}

int		parse_file(t_asm *u)
{
	int 		res;
	t_inst		*cur_inst;
	char		*line;

	if ((res = parse_header(u, &line)) <= 0)
		return (res);
		
	u->insts = (t_inst*)malloc(sizeof(t_inst));
	u->insts->name = ft_strdup("main");
	u->insts->address = 0;
	u->insts->ops = NULL;
	u->insts->prev = NULL;
	u->insts->next = NULL;

	cur_inst = u->insts;

	if (check_line(u, cur_inst, NULL, line) != 0)
	{
		ft_putendl("ERROR CHECK");
		return (0);
	}

	t_inst 		*last_inst;
	t_op_ch		*last_op;

	last_inst = u->insts;
	while (last_inst->next)
		last_inst = last_inst->next;

	if (u->extend && !ft_strcmp(u->insts->name, "main"))
	{
		ft_strdel(&u->insts->name);
		u->insts->name = ft_strdup(last_inst->name);
		
		last_op = last_inst->ops;

		if (last_op)
		{
			while (last_op->next)
				last_op = last_op->next;
			last_op->next = u->insts->ops;
			u->insts->ops->prev = last_op->next;
		}
		else
		{
			last_op = u->insts->ops;
		}
		

	}

	return (1);
}

void 	final_parse(t_asm *u)
{
	t_inst		*cur_inst;
	t_op_ch		*cur_op_ch;
	int			i;
	int 		byte;


	cur_inst = u->insts;
	while (cur_inst)
	{
		if (cur_inst->ops)
			cur_inst->index = u->octal_index;
		
		cur_op_ch = cur_inst->ops;
		while (cur_op_ch)
		{
			cur_op_ch->index = u->octal_index++;
			if (cur_op_ch->op->codage_octal)
				u->octal_index++;
						
			i = -1;

			cur_op_ch->param_codage = 0;
			while (cur_op_ch->params[++i])
			{
				cur_op_ch->params[i] = zap_space_tab(cur_op_ch->params[i]);

				if (cur_op_ch->params[i][0] == 'r')
				{
					cur_op_ch->param_codage |=  1 << (2 * (3 - i));
					
					u->octal_index++;

				}
				else if (ft_isdigit(cur_op_ch->params[i][0]))
				{
					cur_op_ch->param_codage |=  3 << (2 * (3 - i));
					u->octal_index += 2;
				}
				else if (cur_op_ch->params[i][0] == DIRECT_CHAR)
				{
					cur_op_ch->param_codage |= 2 << (2 * (3 - i));

					u->octal_index += cur_op_ch->op->dir_size ? 2 : 4;
				}
				else
				{
					u->octal_index++;
					byte = 254;
				}
			}
			cur_op_ch = cur_op_ch->next;
		}
		cur_inst = cur_inst->next;
	}
}

void 	print_program(t_asm *u)
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
					byte = ft_atoi(cur_op_ch->params[i] + 1);
					write(u->fd_output, &byte, 1);


					ft_putnbr(byte);
					ft_putstr("  ");
				}
				else if (ft_isdigit(cur_op_ch->params[i][0]))
				{
					byte = 0;
					write(u->fd_output, &byte, 1);
					byte = ft_atoi(cur_op_ch->params[i] + 1);
					write(u->fd_output, &byte, 1);


					ft_putnbr(byte);
					ft_putstr("  ");
				}
				else if (cur_op_ch->params[i][0] == DIRECT_CHAR)
				{
					t_inst	*tmp_inst;
					int		tmp_byte;

					if(ft_isdigit(cur_op_ch->params[i][1]) || cur_op_ch->params[i][1] ==  '-')
					{
						tmp_byte = ft_atoi(&cur_op_ch->params[i][1]);

						if (tmp_byte < 0)
							byte = 255;
						else
							byte = 0;

						if (!cur_op_ch->op->dir_size)
						{
							write(u->fd_output, &byte, 1);
							write(u->fd_output, &byte, 1);
						}

						write(u->fd_output, &byte, 1);
						
						
						byte = tmp_byte;
						
						if (tmp_byte < 0)
							byte = 255 + byte + 1;
						
						write(u->fd_output, &byte, 1);

						ft_putnbr(byte);
						ft_putstr("  ");
					}
					else if (cur_op_ch->params[i][1] == LABEL_CHAR)
					{

						tmp_inst = u->insts;

						char *wordo;
						int y;

						y = 2;
						while(ft_strchr(LABEL_CHARS, cur_op_ch->params[i][y]))
							y++;
						if (!y)
						{
							ft_putendl("ERROR 872");
							return ;
						}
						wordo = ft_strsub(cur_op_ch->params[i], 2, y - 2);
						while (tmp_inst && ft_strcmp(tmp_inst->name, wordo))
							tmp_inst = tmp_inst->next;
						
						if (!tmp_inst)
						{
							ft_putendl("ERROR 873");
							return ;
						}
						ft_putnbr(cur_inst->index);
						ft_putstr("  ");
						ft_putnbr(cur_op_ch->index);
						ft_putendl(" ");
						tmp_byte = tmp_inst->index - cur_op_ch->index;

						if (tmp_inst->index > cur_op_ch->index)
							byte = 0;
						else
							byte = 255;

						if (!cur_op_ch->op->dir_size)
						{
							write(u->fd_output, &byte, 1);
							write(u->fd_output, &byte, 1);
						}

						if (tmp_byte < 0)
							tmp_byte = -tmp_byte - 1;

						if (tmp_byte > 255)
							byte -= tmp_byte / 255;
						else
							byte += tmp_byte / 255;
						write(u->fd_output, &byte, 1);

						byte = tmp_byte % 255;
						if (tmp_inst->index > cur_op_ch->index)
							byte = tmp_byte;
						else
							byte = 255 - tmp_byte;
						write(u->fd_output, &byte, 1);

						ft_putnbr(tmp_byte);
						ft_putstr("  ");
						ft_putnbr(byte);
						ft_putstr("  ");
					}
					else
					{
						
						ft_putendl("------------");
						ft_putendl("ERRRRROOORRR");
						ft_putendl(cur_op_ch->params[i]);
						ft_putendl("------------");

					}
					
					// write(u->fd_output, &byte, cur_op_ch->op->dir_size ? 2 : 4);
					
				}
				else
				{
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

int main(int argc, char const *argv[])
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
	final_parse(u);
	print_program(u);
	return (0);
}

