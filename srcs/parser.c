/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:34:34 by nsondag           #+#    #+#             */
/*   Updated: 2019/10/23 12:33:31 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_data		*init_data_label_only(int nb_line, char *label)
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

t_data		*init_data(char *str_para, int nb_line, char *label, char *str_opc)
{
	t_data	*data;

	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	if (!(data->op = identify_opc(str_opc)))
		return (NULL);
	data->codage_octal = 0;
	data->params = ft_strsplit(str_para, SEPARATOR_CHAR);
	data->next = NULL;
	data->nb_line = nb_line;
	data->val_param[0] = 0;
	data->val_param[1] = 0;
	data->val_param[2] = 0;
	data->nb_octet = 0;
	if (label && *label)
		data->label = label;
	else
		data->label = NULL;
	return (data);
}

static int	get_label(t_prog *prog)
{
	t_data	*data;
	t_data	*tmp_data;
	int		i;
	int		j;

	j = 0;
	data = prog->list_data;
	tmp_data = data;
	while ((i = -1) && data)
	{
		if (!(data->op))
		{
			data = data->next;
			continue ;
		}
		if (data->params[i + 1])
			j = (data->params[i + 1][1] == ':') ? 0 : 1;
		while (++i < 3 && data->params[i])
		{
			if (!data->val_param[i] && (data->params[i][1 - j] == ':' ))
				while (tmp_data)
				{
					if (tmp_data->label && !ft_strcmp(tmp_data->label,
								&data->params[i][2 - j]))
					{
						data->val_param[i] = tmp_data->pc - data->pc;
						break ;
					}
					else if (!(tmp_data = tmp_data->next))
						return (data->nb_line);
				}
				tmp_data = prog->list_data;
		}
		data = data->next;
	}
	return (0);
}

int			program_parser(t_prog *prog, t_data *data)
{
	t_data	*tmp_data;
	t_data	*begin_data;
	int		label_error_line;

	begin_data = data;
	while (get_next_line(prog->fd, &prog->full_line) > 0)
	{
		data->line = prog->full_line;
		prog->nb_line++;
		prog->line = skip_chars(prog->full_line, " \t");
		if (!prog->line || *prog->line == '#' || !*prog->line)
			continue;
		if (*prog->line == '.')
			return (manage_errors(prog, 0));
		if (!(tmp_data = parse_commands(prog)))
			return (1);

		tmp_data->pc = data->pc + data->nb_octet;
		if (tmp_data->op && tmp_data->op->opc)
		{
			(!prog->list_data) ? prog->list_data = tmp_data : 0;
			data->next = tmp_data;
			data->next->pc = data->pc + data->nb_octet;
			data->nb_line = prog->nb_line;
			data = data->next;
		}
		else if (tmp_data->label)
		{
			(!prog->list_data) ? prog->list_data = tmp_data : 0;
			data->next = tmp_data;
			data->nb_line = prog->nb_line;
			data = data->next;
		}
	}
	if ((label_error_line = get_label(prog)))
	{
		prog->i = 0;
		return (manage_errors_inexisting_label(begin_data, label_error_line - 1));
	}
	prog->prog_size = data->pc + data->nb_octet;
	close(prog->fd);
	return (0);
}
