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

static int		check_in_label_list(t_prog *prog, int i,
	t_data **tmp, t_data *d)
{
	d->i++;
	while (*tmp)
	{
		if ((*tmp)->label && !ft_strcmp((*tmp)->label, &d->params[i][d->i]))
		{
			d->val_param[i] = (*tmp)->pc - d->pc;
			break ;
		}
		else if (!((*tmp) = (*tmp)->next))
			return (d->nb_line);
	}
	*tmp = prog->list_data;
	return (0);
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
	int		nb_line;

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
				if ((nb_line = check_in_label_list(prog, i, &tmp, d)))
					return (manage_errors_inexisting_label(prog->list_data,
						nb_line - 1));
			}
		}
		d = d->next;
	}
	return (0);
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
			data->line = NULL;
			free_str(prog->line);
			prog->i = 1;
			continue;
		}
		if (prog->line[prog->i] == '.')
			return (err_default(prog, ERROR_COMMAND_IN_PROG) + free_str(prog->line));
		if (!(tmp_data = parse_commands(prog)))
			return (ERROR + free_str(prog->line));
		if ((tmp_data->op && tmp_data->op->opc) || tmp_data->label)
			data = get_pc(prog, tmp_data, data)->next;
	}
	if ((label_error = get_label(prog)))
		return (ERROR);
	prog->prog_size = data->pc + data->nb_octet;
	close(prog->fd);
	return (0);
}
