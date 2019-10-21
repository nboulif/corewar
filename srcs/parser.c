/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:34:34 by nsondag           #+#    #+#             */
/*   Updated: 2019/10/21 15:01:51 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_data	*init_data(char *str_params, int nb_line, char *label, char *str_opc)
{
	t_data	*data;

	if (!(data = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	if (!(data->op = identify_opc(str_opc)))
		return (NULL);
	data->codage_octal = 0;
	data->params = ft_strsplit(str_params, SEPARATOR_CHAR);
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

int		program_parser(t_prog *prog, t_data *data)
{
	t_data	*tmp_data;

	while (prog->nb_line++ && get_next_line(prog->fd, &prog->full_line) > 0)
	{
		prog->line = skip_chars(prog->full_line, " \t");
		if (!prog->line || *prog->line == '#' || !*prog->line)
			continue;
		if (*prog->line == '.')
			return (manage_errors(prog, 0));
		if (!(tmp_data = parse_commands(prog)))
			return (1);
		tmp_data->pc = data->pc + data->nb_octet;
		if (tmp_data->op->opc)
		{
			(!prog->list_data) ? prog->list_data = tmp_data : 0;
			data->next = tmp_data;
			data->next->pc = data->pc + data->nb_octet;
			data = data->next;
		}
	}
	if (get_label(prog))
		manage_errors_inexisting_label(prog);
	prog->prog_size = data->pc + data->nb_octet;
	close(prog->fd);
	return (0);
}
