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

int		handle_extend(t_asm *u)
{
	t_inst 		*last_inst;
	t_op_ch		*last_op;

	last_inst = u->insts;
	while (last_inst->next)
		last_inst = last_inst->next;

	ft_strdel(&u->insts->name);

	if (!(u->insts->name = ft_strdup(last_inst->name)))
	{
		ft_putendl("------------");
		ft_putendl("error 429");
		ft_putendl("------------");
		return (0);
	}
	
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
	
	return (1);
}

int		parse_file(t_asm *u)
{
	int 		res;
	char		*line;


	if ((res = parse_header(u, &line)) <= 0)
		return (res);
		

	if (parse_next_line(u, u->insts, NULL, line) != 0)
	{
		ft_putendl("ERROR CHECK");
		return (0);
	}

	if (u->extend && !ft_strcmp(u->insts->name, "main"))
		return(handle_extend(u));
	return (1);
}