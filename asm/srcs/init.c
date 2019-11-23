/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 13:06:40 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/06 16:48:53 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_data			*init_data_label(t_prog *p, char *label)
{
	t_data	*data;

	if (!(data = (t_data*)malloc(sizeof(t_data))))
	{
		if (label)
			free_str(label);
		return (err_malloc("init data label", p->nb_line)
			&& !free_str(p->line) ? NULL : NULL);
	}
	data->pc = 0;
	data->nb_octet = 0;
	data->line = p->line;
	data->params = NULL;
	data->nb_line = p->nb_line;
	data->op = NULL;
	if (label && *label)
		data->label = label;
	else
		data->label = NULL;
	data->next = NULL;
	return (data);
}

static int		split_params(t_prog *p, t_data *data,
	char *str_para, t_op *op)
{
	int		i;
	char	*final_str;
	int		nb_param;

	i = skip_until(str_para, &i, "#");
	if (!(final_str = ft_strsub(str_para, 0, i)))
		return (err_malloc("ft_strsub on params", p->nb_line) +
			free_data(data));
		data->params = ft_strsplit(final_str, SEPARATOR_CHAR);
	free_str(final_str);
	nb_param = tab_len(data->params);
	if (!data->params || nb_param != op->nb_params)
		return (printf(g_err_msgs[ERROR_WRONG_NB_PARAMS],
			p->nb_line, nb_param, op->nb_params) +
			free_data(data));
	else
		return (0);
}

t_data			*init_data(t_prog *p, char *str_para,
		char *label, t_op *op)
{
	t_data	*data;

	if (!(data = init_data_label(p, label)))
		return (NULL);
	data->op = op;
	data->codage_octal = 0;
	if (split_params(p, data, str_para, op))
		return (NULL);
	data->val_param[0] = 0;
	data->val_param[1] = 0;
	data->val_param[2] = 0;
	data->nb_octet = 0;
	return (data);
}

static int		open_file(t_prog *prog, int argc, char **argv)
{
	int i;

	if (argc < 2)
		return (printf("%s%s%s%s", USAGE1, USAGE2, USAGE3, USAGE4));
	i = 0;
	while (++i <= argc)
	{
		if (*argv[i] == '-')
		{
			if (!ft_strcmp("-a", argv[i]))
				prog->debug = 1;
			else
				return (printf("%s%s%s%s", USAGE1,
					USAGE2, USAGE3, USAGE4));
		}
		else
		{
			prog->fd = open(argv[i], O_RDONLY);
			prog->file_name = argv[i];
			if (prog->fd < 0)
				return (printf(g_err_msgs[ERROR_WRONG_FD], argv[i]));
			break ;
		}
	}
	return (0);
}

t_prog			*init_prog(int argc, char **argv)
{
	t_prog	*prog;

	if (!(prog = (t_prog *)malloc(sizeof(t_prog))))
		return (err_malloc("prog", 0) ? NULL : NULL);
	if (open_file(prog, argc, argv))
	{
		free(prog->line);
		free(prog);
		return (NULL);
	}
	prog->nb_line = 0;
	prog->name = NULL;
	prog->comment = NULL;
	prog->list_data = NULL;
	return (prog);
}
