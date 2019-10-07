/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:34:34 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/22 19:13:43 by nsondag          ###   ########.fr       */
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

int open_file(t_prog *prog, int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Usage: ./asm_res [-a] <sourcefile.s>\n");
		printf("    -a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output\n");
		return (1);
	}
	prog->debug = 0;
	if (argc > 2 && *argv[1] == '-')
	{
		if (!ft_strcmp("-a", argv[1]))
			prog->debug = 1;
		prog->fd = open(argv[2], O_RDONLY);
		if(prog->fd < 0)
			printf("Can't read source file %s\n", argv[2]);
	}
	else
	{
		prog->fd = open(argv[1], O_RDONLY);
		if(prog->fd < 0)
			printf("Can't read source file %s\n", argv[1]);
	}
	return (0);
}

t_prog	*init_prog(int argc, char **argv)
{
	t_prog	*prog;

	prog = (t_prog *)malloc(sizeof(t_prog));
	prog->line = (char *)malloc(sizeof(*prog->line) * 1);
	
	if (open_file(prog, argc, argv))
		return (NULL);
	prog->nb_line = 0;
	prog->name_found = 0;
	prog->comment_found = 0;
	prog->name = NULL;
	prog->comment = NULL;
	prog->list_label = NULL;
	prog->list_data = NULL;
	return (prog);
}

t_label *update_list_label(t_prog *prog, t_data *data)
{
	t_label *new;


	if (data->label)
	{	
		new = (t_label *)malloc(sizeof(t_label));
		new->label = data->label;
		new->pc = data->pc;
		new->next = NULL;
		if (prog->list_label)
			prog->list_label->next = new;
		else 
			prog->list_label = new;
		return (new);
	}
	return (prog->list_label);	
}



int	program_parser(t_prog *prog, t_data	*data)
{
	t_data	*tmp;
	
	while (get_next_line(prog->fd, &prog->full_line) > 0)
	{
		prog->nb_line++;
		prog->line = skip_chars(prog->full_line, " \t");
		if (!prog->line || *prog->line == '#' || !*prog->line)
			continue;
		if (*prog->line == '.')
		{
			if (prog->list_data)
				break;
			return (manage_errors(prog, 0));
		}
		if (!(tmp = parse_commands(prog)))
			return (1);
		tmp->pc = data->pc + data->nb_octet;
		if (tmp->op->opc)
		{
			if (!prog->list_data)
				prog->list_data = tmp;
			data->next = tmp;
			data->next->pc = data->pc + data->nb_octet;
			data = data->next;
		}
		if (tmp->label)
			update_list_label(prog, tmp);
		// if (prog->debug)
		// 		print_data(tmp);
	}
	prog->prog_size = data->pc + data->nb_octet;
	close(prog->fd);
	return (0);
}
