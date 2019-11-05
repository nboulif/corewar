/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:08:16 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/05 18:48:13 by nsondag          ###   ########.fr       */
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
	if (data->params[i][0] == LABEL_CHAR)
		data->params[i] = skip_chars2(&data->params[i][1], LABEL_CHARS);
	else if (data->params[i][0] == '-' || ft_isdigit(data->params[i][0]))
	{
		data->val_param[i] = ft_atoi(data->params[i]);
		data->params[i] += count_digit(data->val_param[i]);
	}
	else
		return (1);
	data->codage_octal |= IND_CODE << (2 * (3 - i));
	data->nb_octet += 2;
	return (0);
}

int		parse_register(t_data *data, int i)
{
	int z;

	z = 0;
	if (data->params[i][1] == '0' && data->params[i][2] &&
			ft_isdigit(data->params[i][2]))
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
	if (data->params[i][1] == LABEL_CHAR)
		data->params[i] = skip_chars2(&data->params[i][2], LABEL_CHARS);
	else if (data->params[i][1] == '-' || ft_isdigit(data->params[i][1]))
	{
		data->val_param[i] = ft_atoi(&data->params[i][1]);
		data->params[i] += count_digit_string(&data->params[i][1]) + 1;
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

int		parse_params_2(t_prog *prog, t_data *d, int i, char *ori_param)
{
	if (!d->params[i])
		return (manage_errors(prog, prog->i));
	if (d->params[i][0] == 'r' && d->params[i][1] &&
			ft_isdigit(d->params[i][1]))
	{
		if (!(d->op->params[i] & T_REG))
			return (printf("%s %d %s %s\n", PARAM, i, TYPE_REG, d->op->name));
		if (!parse_register(d, i))
			return (0);
	}
	else if (d->params[i][0] == DIRECT_CHAR)
	{
		if (!(d->op->params[i] & T_DIR))
			return (printf("%s %d %s %s\n", PARAM, i, TYPE_INDIR, d->op->name));
		if (!parse_direct_char(d, i))
			return (0);
	}
	else if (d->params[i][0] == '-' || ft_isdigit(d->params[i][0]) || d->params[i][0] == LABEL_CHAR)
	{
		if (!(d->op->params[i] & T_IND))
			return (printf("%s %d %s %s\n", PARAM, i, TYPE_DIR, d->op->name));
		if (!parse_indirect(d, i))
			return (0);
	}
	return (manage_errors(prog, prog->i + (int)(d->params[i] - ori_param)));
}

int		parse_params(t_prog *p, t_data *d)
{
	int		i;
	char	*ori_param;
	char	*tmp_param;

	if (d->op->codage_octal)
		d->nb_octet++;
	i = -1;
	while (++i < d->op->nb_params)
	{
		ori_param = d->params[i];
		d->params[i] = skip_chars2(d->params[i], " \t");
		tmp_param = d->params[i];
		if (parse_params_2(p, d, i, ori_param))
			return (1);
		d->params[i] = skip_chars2(d->params[i], " \t");
		if (d->params[i] && *d->params[i] && *d->params[i] != '#'
				&& *d->params[i] != ';')
			return (manage_errors(p, p->i + (int)(d->params[i] - ori_param)));
		d->params[i] = trim_comments_space(tmp_param);
		p->i += ft_strlen(ori_param) + 1;
	}
	d->nb_octet++;
	return (0);
}

t_data	*parse_commands(t_prog *prog)
{
	char	*opc;
	char	*label;
	t_data	*data;
	int		skip_len;

	label = "";
	skip_len = skip_until(prog->line, &prog->i, ":% \t");
	if (!prog->line[prog->i])
	{
		manage_errors(prog, prog->i);
		return (NULL);
	}
	if (prog->line[prog->i] == ':')
	{
		label = ft_strsub(prog->line, prog->i - skip_len, skip_len);
		skip_nb_chars(prog->line, &prog->i, 1);
		skip_chars(prog->line, &prog->i, " \t");
		if (!prog->line[prog->i])
			return (init_data_label(prog->nb_line, label));
		skip_len = skip_until(prog->line, &prog->i, ":% \t");
	}
	if (prog->line[prog->i])
		opc = ft_strsub(prog->line, prog->i - skip_len,  skip_len);
	if (prog->line[prog->i] && prog->line[prog->i] != '%')
		skip_nb_chars(prog->line, &prog->i, 1);
	if (!prog->line[prog->i])
	{
		manage_errors(prog, prog->i);
		return (NULL);
	}
	if (!(data = init_data(&prog->line[prog->i], prog->nb_line, label, opc)))
	{
		manage_errors(prog, prog->i);
		return (NULL);
	}
	if (prog->line[prog->i])
		return (!parse_params(prog, data) ? data : NULL);
	return (data);
}
