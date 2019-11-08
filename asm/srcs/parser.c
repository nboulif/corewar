/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 13:06:40 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/06 16:48:53 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_data			*init_data_label(int nb_line, char *label)
{
	t_data	*data;

	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	data->op = NULL;
	data->nb_line = nb_line;
	if (label && *label)
		data->label = label;
	else
		data->label = NULL;
	data->next = NULL;
	return (data);
}

t_data			*init_data(char *str_para, int nb_line,
		char *label, char *str_opc)
{
	t_data	*data;

	if (!(data = init_data_label(nb_line, label)))
		return (NULL);
	if (!(data->op = identify_opc(str_opc)))
		return (NULL);
	data->codage_octal = 0;
	data->params = ft_strsplit(str_para, SEPARATOR_CHAR);
	data->val_param[0] = 0;
	data->val_param[1] = 0;
	data->val_param[2] = 0;
	data->nb_octet = 0;
	return (data);
}

/*
** t_data d:	data a parcourir pour completer la valeur des labels
** t_data tmp:	data a parcourir pour trouver les labels
** i:			index du parametre
** j:			index de la chaine de caractere du parametre
**
** parcours la liste de data
** parcours les params de cette data si data est plus qu'un label (d->op)
** Pour chaque param qui a un label_char
** parcours la liste de data pour chercher le label tant que val_param
** s'il existe la valeur du parametre vaut la difference des pc -> retour 0
** sinon -> retour nb_line
*/

static int		get_label(t_prog *prog)
{
	t_data	*d;
	t_data	*tmp;
	int		i;

	d = prog->list_data;
	tmp = d;
	while ((i = -1) && d)
	{
		while (d->op && ++i < 3 && d->params[i])
		{
			d->i = 0;
			skip_until(d->params[i], &d->i, ":");
			if (d->params[i][d->i] == ':')
			{
				d->i++;
				while (tmp)
				{
					if (tmp->label && !ft_strcmp(tmp->label, &d->params[i][d->i]))
					{
						d->val_param[i] = tmp->pc - d->pc;
						break ;
					}
					else if (!(tmp = tmp->next))
						return (d->nb_line);
				}
				tmp = prog->list_data;
			}
		}
		d = d->next;
	}
	return (0);
}

static t_data	*get_pc(t_prog *prog, t_data *tmp_data, t_data *data)
{
	tmp_data->pc = data->pc + data->nb_octet;
	(!prog->list_data) ? prog->list_data = tmp_data : 0;
	data->next = tmp_data;
	if (tmp_data->op && tmp_data->op->opc)
		data->next->pc = data->pc + data->nb_octet;
	data->nb_line = prog->nb_line;
	return (data);
}

int				program_parser(t_prog *prog, t_data *data)
{
	t_data	*tmp_data;
	t_data	*begin_data;
	int		label_error;

	begin_data = data;
	while (get_next_line(prog->fd, &prog->line) > 0)
	{
		prog->i = 0;
		data->line = prog->line;
		prog->nb_line++;
		skip_chars(prog->line, &prog->i, " \t");
		if (!prog->line || prog->line[prog->i] == '#' || !prog->line[prog->i])
		{
			prog->i = 1;
			continue;
		}
		if (prog->line[prog->i] == '.')
			return (manage_errors(prog, 0));
		if (!(tmp_data = parse_commands(prog)))
		{
			printf("test\n");
			return (1);
		}
		if ((tmp_data->op && tmp_data->op->opc) || tmp_data->label)
			data = get_pc(prog, tmp_data, data)->next;
	}
	if ((label_error = get_label(prog)))
		return (manage_errors_inexisting_label(begin_data, label_error - 1));
	prog->prog_size = data->pc + data->nb_octet;
	close(prog->fd);
	return (0);
}