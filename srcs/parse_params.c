/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:08:16 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/13 20:05:14 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	*identify_opc(char *line)
{
	int		i;

	i = -1;

	if (!*line)
			return(&g_op_tab[16]);
	while (++i < 17)
	{
		if (!ft_strcmp(line, g_op_tab[i].name))
			return (&g_op_tab[i]);
	}
	return (NULL);
}

int parse_indirect(t_data *data, int i)
{
	data->val_param[i] = ft_atoi(data->params[i]);
	data->params[i] += count_digit(data->val_param[i]);
	data->codage_octal |= IND_CODE << (2 * (3 - i));
	data->nb_octet += 2;
	return (0);
}

int parse_register(t_data *data, int i)
{
	data->val_param[i] = ft_atoi(&data->params[i][1]);
	if (!(data->val_param[i] > 0 && data->val_param[i] < 17  && (data->op->params[i] & T_REG)))
		return (printf("error2\n"));
	data->params[i] += count_digit(data->val_param[i]) + 1;
	data->codage_octal |= REG_CODE << (2 * (3 - i));
	data->nb_octet++;
	return (0);
}

int parse_direct_char(t_data *data, int i)
{
	if (data->params[i][1] == LABEL_CHAR)
		data->params[i] = skip_chars(&data->params[i][2], LABEL_CHARS);
	else if (data->params[i][1] == '-' || ft_isdigit(data->params[i][1]))
	{
		data->val_param[i] = ft_atoi(&data->params[i][1]);
		data->params[i] += count_digit(data->val_param[i]) + 1;
	}
	else
		return (printf("error3\n"));
	data->codage_octal |= DIR_CODE << (2 * (3 - i));
	if (data->op->dir_size == 1)
		data->nb_octet += 2;
	else
	{
		// printf("4 octets\n");
		data->nb_octet += 4;
	}
	return (0);
}

int parse_params(t_prog *prog, t_data *data)
{
	int		i;
	char	*tmp1;
	char	*tmp;

	if (data->op->codage_octal)
		data->nb_octet++;
	i = -1;
	while (++i < data->op->nb_params)
	{
		tmp1 = data->params[i];
		data->params[i] = skip_chars(data->params[i], " \t");
		tmp = data->params[i];
		if (!data->params[i])
			return (printf("error1\n"));
		if (data->params[i][0] == 'r')
			parse_register(data, i);
		else if (data->params[i][0] == DIRECT_CHAR)
			parse_direct_char(data, i);
		else if (data->params[i][0] == '-' || ft_isdigit(data->params[i][0]))
			parse_indirect(data, i);
		else
			return (printf("error4\n"));
		data->params[i] = skip_chars(data->params[i], " \t");
		if (data->params[i] && *data->params[i] && *data->params[i] != '#' && *data->params[i] != ';')
			return (manage_errors(prog, prog->i + (int)(data->params[i] - tmp1)));
		data->params[i] = tmp;
		prog->i += ft_strlen(tmp1) + 1;
	}
	data->nb_octet++;
	return (0);
}

t_data	*parse_commands(t_prog *prog)
{
	char	*opc;
	char	*label;
	t_data	*data;
	int		i;
	int		y;

	label = "";
	y = 0;
	while (prog->line[y] && prog->line[y] != ':' && prog->line[y] != '%' && prog->line[y] != ' ' && prog->line[y] != '\t')
		y++;
	if (!prog->line[y])
	{
		manage_errors(prog, y);
		return (NULL);
	}
	if (prog->line[y] == ':')
	{
		label = ft_strsub(prog->line, 0, y);
		while (prog->line[y + 1] == ' ' || prog->line[y + 1] == '\t')
			y++;
		prog->line = prog->line + ++y;
	}
	i = 0;
	while (prog->line[i] && prog->line[i] != ' ' && prog->line[i] != '\t' && prog->line[i] != '%')
		i++;
	opc = ft_strsub(prog->line, 0, i);
	if (prog->line[i] && prog->line[i] != '%')
		prog->line = prog->line + i + 1;
	else
		prog->line = prog->line + i;
	data = init_data(prog->line, prog->nb_line, label, opc);
	prog->i = (int)(prog->line - prog->full_line);
	if	(*prog->line)
		return(!parse_params(prog, data) ? data : NULL);
	return (data);
}