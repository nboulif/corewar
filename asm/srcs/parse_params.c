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

int		parse_register(t_prog *prog, t_data *data, int i)
{
	data->i++;
	data->val_param[i] = ft_atoi(&data->params[i][data->i]);
	if (!(data->val_param[i] >= 0 && data->val_param[i] <= 99))
		return (printf(g_err_msgs[ERROR_INVALID_REG_NUMBER],
			prog->nb_line, data->val_param[i]));
	else
	{
		data->i += count_digit_string(&data->params[i][data->i]);
		data->codage_octal |= REG_CODE << (2 * (3 - i));
		data->nb_octet++;
		return (OK);
	}
}

int		parse_non_register(t_prog *prog, t_data *d, int i, int type)
{
	int code;

	if (d->params[i][d->i] == LABEL_CHAR)
	{
		d->i++;
		skip_chars(d->params[i], &d->i, LABEL_CHARS);
	}
	else if (ft_isdigit(d->params[i][d->i]) ||
		(d->params[i][d->i + 1] && d->params[i][d->i] == '-'
		&& ft_isdigit(d->params[i][d->i + 1])))
	{
		d->val_param[i] = ft_atoi(&d->params[i][d->i]);
		d->i += count_digit_string(&d->params[i][d->i]);
	}
	else
		return (printf(g_err_msgs[ERROR_INVALID_IND_DIR], d->params[i],
			(type == T_IND) ? "T_IND" : "T_DIR", prog->nb_line, i + 1));
			code = type == T_IND ? IND_CODE : DIR_CODE;
	d->codage_octal |= code << (2 * (3 - i));
	if (d->op->dir_size == 1 || type == T_IND)
		d->nb_octet += 2;
	else
		d->nb_octet += 4;
	return (OK);
}

int		parse_one_param(t_prog *prog, t_data *d, int i)
{
	int res;

	if (!d->params[i] || !d->params[i][d->i])
		return (printf(g_err_msgs[ERROR_EMPTY_PARAM], i + 1, prog->nb_line));
	res = OK;
	if (d->params[i][d->i] == 'r')
	{
		if (!(d->op->params[i] & T_REG))
			return (err_param_type(prog, "T_REG", i + 1));
		res = parse_register(prog, d, i);
	}
	else if (d->params[i][d->i] == DIRECT_CHAR)
	{
		d->i++;
		if (!(d->op->params[i] & T_DIR))
			return (err_param_type(prog, "T_DIR", i + 1));
		res = parse_non_register(prog, d, i, T_DIR);
	}
	else
	{
		if (!(d->op->params[i] & T_IND))
			return (err_param_type(prog, "T_IND", i + 1));
		res = parse_non_register(prog, d, i, T_IND);
	}
	return (res);
}

int		parse_params(t_prog *p, t_data *d)
{
	int		i;
	int		to_delete;
	char	*tmp_params;

	if (d->op->codage_octal)
		d->nb_octet++;
	i = -1;
	while (++i < d->op->nb_params)
	{
		d->i = 0;
		skip_chars(d->params[i], &d->i, " \t");
		if (parse_one_param(p, d, i))
			return (ERROR);
		to_delete = skip_chars(d->params[i], &d->i, " \t");
		if (d->params[i][d->i] &&
			(i + 1 < d->op->nb_params || d->params[i][d->i] != '#'))
			return (err_lexical(p, 98, p->i + d->i));
		tmp_params = d->params[i];
		d->params[i] = ft_strsub(d->params[i], 0, d->i - to_delete);
		free_str(tmp_params);
		p->i += d->i + 1;
	}
	d->nb_octet++;
	return (0);
}

t_data	*parse_opc(t_prog *prog, int skip_len, char *label)
{
	t_op	*op;
	char	*str_opc;
	t_data	*data;

	str_opc = ft_strsub(prog->line, prog->i - skip_len, skip_len);
	skip_chars(prog->line, &prog->i, " \t");
	if (!prog->line[prog->i] && !free_str(str_opc))
		return (err_lexical(prog, 57, prog->i) ? NULL : NULL);
	op = identify_opc(str_opc);
	free_str(str_opc);
	if (!(op))
		return (printf(g_err_msgs[ERROR_INDENTIFY_OPC], prog->nb_line, str_opc)
			? NULL : NULL);
	else if (!(data = init_data(prog, &prog->line[prog->i], label, op)))
		return (NULL);
	else if (prog->line[prog->i])
		return (parse_params(prog, data) && !free_data(data) ? NULL : data);
	return (err_lexical(prog, 32, prog->i) && !free_data(data) ? NULL : NULL);
}

t_data	*parse_label(t_prog *prog, int *skip_len)
{
	char	*label;
	t_data	*data;

	if (!(label = ft_strsub(prog->line, prog->i - *skip_len, *skip_len)))
		return (err_malloc("str_sub_label", prog->nb_line) ? NULL : NULL);
	prog->i++;
	skip_chars(prog->line, &prog->i, " \t");
	if (!prog->line[prog->i] || prog->line[prog->i] == '#')
	{
		data = init_data_label(prog, label);
		if (!data)
			return (NULL);
		return (data);
	}
	*skip_len = skip_until(prog->line, &prog->i, ":% \t");
	if (prog->line[prog->i])
	{
		data = parse_opc(prog, *skip_len, label);
		if (!data)
			return (NULL);
		return (data);
	}
	free_str(label);
	return (err_lexical(prog, 36, prog->i - *skip_len) ? NULL : NULL);
}

t_data	*parse_commands(t_prog *prog)
{
	char	*label;
	int		skip_len;

	label = "";
	skip_chars(prog->line, &prog->i, " \t");
	skip_len = skip_until(prog->line, &prog->i, ":% \t");
	if (!prog->line[prog->i])
		return ((void*)(long)!(err_lexical(prog, 65, prog->i) +
		free_str(prog->line)));
	else if (prog->line[prog->i] == ':')
		return (parse_label(prog, &skip_len));
	return (parse_opc(prog, skip_len, NULL));
}
