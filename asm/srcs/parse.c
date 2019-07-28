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

#include "asm.h"

char	*zap_space_tab(char *line)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	return (line);
}


int		parse_header(t_asm *u, char **line)
{
	int			res;
	char		**splited;

	
	while ((res = get_next_line(u->fd_input, &(*line))) == 1)
	{
		if ((*line)[0] == '#')
		{
			ft_strdel(&(*line));
			continue;
		}
		else if (ft_strstr((*line), NAME_CMD_STRING))
		{
			splited = ft_strsplit(*line, '"');
			ft_strncpy(u->prog->prog_name, splited[1], PROG_NAME_LENGTH);
			ft_strdel(&(*line));
			ft_tabdel(&splited);

		}
		else if (ft_strstr((*line), COMMENT_CMD_STRING))
		{
			splited = ft_strsplit(*line, '"');
			ft_strncpy(u->prog->comment, splited[1], COMMENT_LENGTH);
			ft_strdel(&(*line));
			ft_tabdel(&splited);

		}
		else if (ft_strstr((*line), ".extend"))
			u->prog->extend = 1;
		else
			break ;
	}

	return (res);

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
	cur_op_ch->params = ft_strsplit(line, SEPARATOR_CHAR);

	if (!cur_op_ch->params || !parse_params(u, cur_op_ch))
		return(-1);	
	

	ft_strdel(&line_o);

	return (parse_next_line(u, cur_inst, cur_op_ch, line));
}

int		parse_file(t_asm *u)
{
	int 		res;
	char		*line;


	if ((res = parse_header(u, &line)) <= 0)
		return (res);
		

	if (parse_next_line(u, u->prog->insts, NULL, line) != 0)
	{
		ft_putendl("ERROR CHECK");
		return (0);
	}

	if (u->prog->extend && !ft_strcmp(u->prog->insts->name, "main"))
		return(handle_extend(u));
	return (1);
}