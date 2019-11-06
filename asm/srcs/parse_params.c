/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:08:16 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/06 16:40:07 by nsondag          ###   ########.fr       */
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

int		parse_register(t_data *data, int i)
{
	data->i++;
	data->val_param[i] = ft_atoi(&data->params[i][data->i]);
	if (!(data->val_param[i] >= 0 && data->val_param[i] <= 99))
		return (1);
	data->i += count_digit_string(&data->params[i][data->i]);
	data->codage_octal |= REG_CODE << (2 * (3 - i));
	data->nb_octet++;
	return (0);
}

int		parse_non_register(t_data *d, int i, int type)
{
	int code;

	if (d->params[i][d->i] == LABEL_CHAR)
	{
		d->i++;
		skip_chars(d->params[i], &d->i, LABEL_CHARS);
	}
	else if (d->params[i][d->i] == '-' || ft_isdigit(d->params[i][d->i]))
	{
		d->val_param[i] = ft_atoi(&d->params[i][d->i]);
		d->i += count_digit_string(&d->params[i][d->i]);
	}
	else
		return (1);
	code = (type == T_IND) ? IND_CODE : DIR_CODE;
	d->codage_octal |= code << (2 * (3 - i));
	if (d->op->dir_size == 1 || type == T_IND)
		d->nb_octet += 2;
	else
		d->nb_octet += 4;
	return (0);
}

int		parse_params_2(t_prog *prog, t_data *d, int i)
{
	if (!d->params[i])
		return (manage_errors(prog, prog->i + d->i));
	if (d->params[i][d->i] == 'r')
	{
		if (!(d->op->params[i] & T_REG))
			return (printf("%s %d %s %s\n", PARAM, i, TYPE_REG, d->op->name));
		if (!parse_register(d, i))
			return (0);
	}
	else if (d->params[i][d->i] == DIRECT_CHAR)
	{
		d->i++;
		if (!(d->op->params[i] & T_DIR))
			return (printf("%s %d %s %s\n", PARAM, i, TYPE_INDIR, d->op->name));
		if (!parse_non_register(d, i, T_DIR))
			return (0);
	}
	else
	{
		if (!(d->op->params[i] & T_IND))
			return (printf("%s %d %s %s\n", PARAM, i, TYPE_DIR, d->op->name));
		if (!parse_non_register(d, i, T_IND))
			return (0);
	}
	return (manage_errors(prog, prog->i + d->i));
}

int		parse_params(t_prog *p, t_data *d)
{
	int		i;
	int		to_delete;

	if (d->op->codage_octal)
		d->nb_octet++;
	i = -1;
	while (++i < d->op->nb_params)
	{
		d->i = 0;
		skip_chars(d->params[i], &d->i, " \t");
		if (parse_params_2(p, d, i))
			return (1);
		to_delete = skip_chars(d->params[i], &d->i, " \t");
		if (d->params[i] && d->params[i][d->i] && d->params[i][d->i] != '#')
			return (manage_errors(p, p->i + d->i));
		d->params[i] = ft_strsub(d->params[i], 0, d->i - to_delete);
		p->i += d->i + 1;
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
	skip_chars(prog->line, &prog->i, " \t");
	skip_len = skip_until(prog->line, &prog->i, ":% \t");
	if (!prog->line[prog->i])
	{
		manage_errors(prog, prog->i);
		return (NULL);
	}
	if (prog->line[prog->i] == ':')
	{
		label = ft_strsub(prog->line, prog->i - skip_len, skip_len);
		prog->i++;
		skip_chars(prog->line, &prog->i, " \t");
		if (!prog->line[prog->i])
			return (init_data_label(prog->nb_line, label));
		skip_chars(prog->line, &prog->i, " \t");
		skip_len = skip_until(prog->line, &prog->i, ":% \t");
	}
	if (prog->line[prog->i])
		opc = ft_strsub(prog->line, prog->i - skip_len, skip_len);
	if (prog->line[prog->i] && prog->line[prog->i] != '%')
		prog->i++;
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
