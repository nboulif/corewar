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

t_data			*parse_opc(t_prog *prog, int skip_len, char *label)
{
	t_op	*op;
	char	*str_opc;
	t_data	*data;

	str_opc = ft_strsub(prog->line, prog->i - skip_len, skip_len);
	skip_chars(prog->line, &prog->i, " \t");
	if (!prog->line[prog->i] && !free_str(str_opc))
		return (err_lexical(prog, 57, prog->i) ? NULL : NULL);
	op = identify_opc(str_opc);
	if (!op)
	{
		label ? free_str(label) : 0;
		return (printf(g_err_msgs[ERROR_INDENTIFY_OPC], prog->nb_line, str_opc)
			+ free_str(prog->line) + free_str(str_opc) ? NULL : NULL);
	}
	free_str(str_opc);
	if (!(data = init_data(prog, &prog->line[prog->i], label, op)))
		return (NULL);
	else if (prog->line[prog->i])
		return (parse_params(prog, data) && !free_data(data) ? NULL : data);
	return (err_lexical(prog, 32, prog->i) && !free_data(data) ? NULL : NULL);
}

t_data			*parse_label(t_prog *prog, int *skip_len)
{
	char	*label;

	if (!(label = ft_strsub(prog->line, prog->i - *skip_len, *skip_len)))
		return (err_malloc("str_sub_label", prog->nb_line) ? NULL : NULL);
	prog->i++;
	skip_chars(prog->line, &prog->i, " \t");
	if (!prog->line[prog->i] || prog->line[prog->i] == COMMENT_CHAR)
		return (init_data_label(prog, label));
	*skip_len = skip_until(prog->line, &prog->i, ":% \t");
	if (prog->line[prog->i])
		return (parse_opc(prog, *skip_len, label));
	free_str(label);
	free_str(prog->line);
	return (err_lexical(prog, 39, prog->i - *skip_len) ? NULL : NULL);
}

t_data			*parse_commands(t_prog *prog)
{
	int		skip_len;

	skip_chars(prog->line, &prog->i, " \t");
	skip_len = skip_until(prog->line, &prog->i, ":% \t");
	if (!prog->line[prog->i])
		return ((void*)(long)!(err_lexical(prog, 65, prog->i) +
		free_str(prog->line)));
	else if (prog->line[prog->i] == ':')
		return (parse_label(prog, &skip_len));
	return (parse_opc(prog, skip_len, NULL));
}

t_data			*get_pc(t_prog *prog, t_data *old_data, t_data *data)
{
	data->pc = old_data ? old_data->pc + old_data->nb_octet : 0;
	if (old_data)
		old_data->next = data;
	if (!prog->list_data)
		prog->list_data = data;
	return (data);
}

int				program_parser(t_prog *prog, t_data *data, t_data *old_data)
{
	int		last_res;
	int		res;

	last_res = 0;
	while ((res = get_next_line(prog->fd, &prog->line)) > 0)
	{
		last_res = prog->line[0] == '#' ? 2 : res;
		prog->i = 0;
		prog->nb_line++;
		skip_chars(prog->line, &prog->i, " \t");
		!prog->line[prog->i] ? last_res = 2 : 0;
		if ((!prog->line || !prog->line[prog->i] ||
			prog->line[prog->i] == COMMENT_CHAR) && !free_str(prog->line))
			continue;
		else if (prog->line[prog->i] == '.')
			return (err_default(prog,
				ERROR_COMMAND_IN_PROG) + free_str(prog->line));
			old_data = data;
		if (!(data = parse_commands(prog)))
			return (ERROR);
		get_pc(prog, old_data, data);
	}
	free(prog->line);
	prog->prog_size = data ? data->pc + data->nb_octet : 0;
	return (last_res == 1 ? printf("No end line\n") : OK);
}
