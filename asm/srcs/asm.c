/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:10:31 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/08 16:28:08 by nsondag          ###   ########.fr       */
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

static int		check_list_label(t_prog *prog)
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
						nb_line));
			}
		}
		d = d->next;
	}
	return (0);
}

int				main(int argc, char **argv)
{
	t_prog	*prog;

	if (!(prog = init_prog(argc, argv)))
		return (1);
	if (get_header(prog))
		return (free_prog(prog) + 1);
	if (prog->nb_line <= 0)
		return (ft_printf("Empty program\n") + free_prog(prog));
	if (!program_parser(prog, NULL, NULL))
	{
		if (prog->prog_size == 0)
			return (ft_printf("Empty program\n") + free_prog(prog));
		else if (check_list_label(prog))
			return (free_prog(prog) + 1);
		prog->debug ? print_debug(prog) : write_file(prog);
	}
	close(prog->fd);
	free_prog(prog);
	return (0);
}
