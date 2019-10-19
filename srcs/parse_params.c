/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:08:16 by nsondag           #+#    #+#             */
/*   Updated: 2019/10/19 16:06:17 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op	*identify_opc(char *line)
{
	int i;

	i = -1;
	if (!*line)
		return (&g_op_tab[16]);
	while (++i < 16)
	{
		if (!ft_strcmp(line, g_op_tab[i].name))
			return (&g_op_tab[i]);
	}
	return (NULL);
}

int		parse_indirect(t_data *data, int i)
{
	data->val_param[i] = ft_atoi(data->params[i]);
	data->params[i] += count_digit(data->val_param[i]);
	data->codage_octal |= IND_CODE << (2 * (3 - i));
	data->nb_octet += 2;
	return (0);
}

int		parse_register(t_data *data, int i)
{
	int z;

	z = 0;
	if (data->params[i][1] == '0' && data->params[i][2] && ft_isdigit(data->params[i][2]))
		z++;
	data->val_param[i] = ft_atoi(&data->params[i][1 + z]);
	if (!(data->val_param[i] >= 0 && data->val_param[i] <= 99))
		return (1);
	data->params[i] += count_digit(data->val_param[i]) + 1 + z;
	data->codage_octal |= REG_CODE << (2 * (3 - i));
	data->nb_octet++;
	return (0);
}

int		parse_direct_char(t_data *data, int i)
{
	if (data->params[i][0] == LABEL_CHAR || data->params[i][1] == LABEL_CHAR)
	{
		if (data->params[i][0] == LABEL_CHAR)
			data->params[i] = skip_chars(&data->params[i][1], LABEL_CHARS);
		else
			data->params[i] = skip_chars(&data->params[i][2], LABEL_CHARS);
	}
	else if (data->params[i][1] == '-' || ft_isdigit(data->params[i][1]))
	{
		data->val_param[i] = ft_atoi(&data->params[i][1]);
		data->params[i] += count_digit(data->val_param[i]) + 1;
	}
	else
		return (1);
	data->codage_octal |= DIR_CODE << (2 * (3 - i));
	if (data->op->dir_size == 1)
		data->nb_octet += 2;
	else
		data->nb_octet += 4;
	return (0);
}

int		parse_params_2(t_prog *prog, t_data *data, int i, char *ori_param)
{
	if (!data->params[i])
		return (manage_errors(prog, prog->i));
	if (data->params[i][0] == 'r' && data->params[i][1] && ft_isdigit(data->params[i][1]))
	{
		if (!(data->op->params[i] & T_REG))
			return (printf("Invalid parameter %d type register for instruction %s\n", i, data->op->name));
		if (!parse_register(data, i))
			return (0);
	}
	else if (data->params[i][0] == DIRECT_CHAR || data->params[i][0] == LABEL_CHAR)
	{
		if (!(data->op->params[i] & T_DIR))
			return (printf("Invalid parameter %d type direct for instruction %s\n", i, data->op->name));
		if (!parse_direct_char(data, i))
			return (0);
	}
	else if (data->params[i][0] == '-' || ft_isdigit(data->params[i][0]))
	{
		if (!(data->op->params[i] & T_IND))
			return (printf("Invalid parameter %d type indirect for instruction %s\n", i, data->op->name));
		if (!parse_indirect(data, i))
			return (0);
	}
	return (manage_errors(prog, prog->i + (int)(data->params[i] - ori_param)));
}

int		parse_params(t_prog *prog, t_data *data)
{
	int		i;
	int		j;
	char	*ori_param;
	char	*tmp_param;

	if (data->op->codage_octal)
		data->nb_octet++;
	i = -1;
	while (++i < data->op->nb_params)
	{
		ori_param = data->params[i];
		data->params[i] = skip_chars(data->params[i], " \t");
		tmp_param = data->params[i];
		if (parse_params_2(prog, data, i, ori_param))
			return (1);
		data->params[i] = skip_chars(data->params[i], " \t");
		if (data->params[i] && *data->params[i] && *data->params[i] != '#' && *data->params[i] != ';')
			return (manage_errors(prog, prog->i + (int)(data->params[i] - ori_param)));
		data->params[i] = tmp_param;
		//------------Trim spaces and comments of params
		j = 0;
		while (data->params[i][j] && data->params[i][j] != ' ' && data->params[i][j] != '\t' && data->params[i][j] != '#')
			j++;
		data->params[i] = ft_strsub(data->params[i], 0, j);
		//------------
		prog->i += ft_strlen(ori_param) + 1;
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
	if (!*prog->line)
	{
		manage_errors(prog, y + i + 1);
		return (NULL);
	}
	if (!(data = init_data(prog->line, prog->nb_line, label, opc)))
	{
		manage_errors(prog, y + i - 1);
		return (NULL);
	}
	prog->i = (int)(prog->line - prog->full_line);
	if (*prog->line)
		return (!parse_params(prog, data) ? data : NULL);
	return (data);
}
