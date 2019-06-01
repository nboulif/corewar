/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_op_inst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op_ch			*define_operation(t_asm *u, t_inst *cur_inst, t_op_ch *cur_op_ch, t_op *op)
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

		cur_inst->index = u->octal_index;
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

int		parse_params(t_asm *u, t_op_ch *cur_op_ch)
{
	int i;

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
			cur_op_ch->param_codage |=  REG_CODE << (2 * (3 - i));
			u->octal_index++;
		}
		else if(ft_isdigit(cur_op_ch->params[i][0]) || cur_op_ch->params[i][0] == '-')
		{
			cur_op_ch->param_codage |= IND_CODE << (2 * (3 - i));
			u->octal_index += 2;
		}
		else if (cur_op_ch->params[i][0] == DIRECT_CHAR)
		{
			cur_op_ch->param_codage |= DIR_CODE << (2 * (3 - i));
			u->octal_index += cur_op_ch->op->dir_size ? 2 : 4;
		}
		else
		{
		ft_putendl("ERROR 026");
			return(0);	
		}
	}
	return (1);
}

int		parse_next_line(t_asm *u, t_inst *cur_inst, t_op_ch *cur_op_ch, char *line)
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
		return (parse_next_line(u, cur_inst, cur_op_ch, line));
	if (!(word = retrieve_next_world(&line)))
		return (parse_next_line(u, cur_inst, cur_op_ch, line));

	op = check_if_operation(word);
	
	if ((!op || !ft_strcmp("live", word)) && (*line == LABEL_CHAR || !ft_strcmp("main", cur_inst->name)))
	{
		line++;
		if (!(cur_inst = define_instruction(u, cur_inst, word)))
			return (0);
		
		cur_op_ch = NULL;
		if (!(word = retrieve_next_world(&line)))
			return (parse_next_line(u, cur_inst, NULL, line));
		op = check_if_operation(word);
	}

	if (!(cur_op_ch = define_operation(u, cur_inst, cur_op_ch, op)))
		return (-1);

	line = zap_space_tab(line);
	cur_op_ch->params = ft_strsplit(line, ',');

	if (!cur_op_ch->params || !parse_params(u, cur_op_ch))
		return(-1);	
	

	ft_strdel(&line_o);

	return (parse_next_line(u, cur_inst, cur_op_ch, line));
}