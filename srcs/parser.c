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

t_prog	*init_prog(int argc, char **argv)
{
	t_prog	*prog;

	prog = (t_prog *)malloc(sizeof(t_prog));
	prog->line = (char *)malloc(sizeof(*prog->line) * 1);
	if (argc < 2)
	{
		printf("print usage\n");
		return (NULL);
	}
	prog->fd = open(argv[1], O_RDONLY);
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

int print_data(t_data	*data)
{
	int i;
	int y;
	
	if (data->label)
		printf("%-11d :    %s:\n", data->pc, data->label);
	if (data->op->opc)
	{
		printf("%-5d (%-3d) :        %-10s ", data->pc, data->nb_octet, data->op->name);
		i = 0;
		while(i < data->op->nb_params)
		{
			y = 0;
			while(data->params[i][y] && data->params[i][y] != ' ' && data->params[i][y] != '\t')
				y++;
			printf("%-18.*s", y, data->params[i++]);
		}
		printf("\n");

		printf("%20s %-4d", "", data->op->opc);
		data->op->codage_octal ? printf(" %-6d", data->codage_octal) : printf(" %-6s", "");
		
		i = 0;
		while(i < data->op->nb_params)
		{
			if (((data->codage_octal >> (2 * (3 - i))) & 3) == T_DIR)
			{
				y = 0;
				while (y < 4)
				{
					if (y < (data->op->dir_size ? 2 : 4))
						printf("%-4u", (uint8_t)(data->val_param[i] >> (8 * (3 - y))));
					else
						printf("    ");
					y++;
				}
				printf("  ");
			}
			else
				printf("%-18d", data->val_param[i]);
			i++;
		}
		printf("\n");
		
		printf("%20s %-4d", "", data->op->opc);
		data->op->codage_octal ? printf(" %-6d", data->codage_octal) : printf(" %-6s", "");
		i = 0;
		while(i < data->op->nb_params)
			printf("%-18d", data->val_param[i++]);
		printf("\n");

		printf("\n");
		data = data->next;
	}
	return (0);
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
		print_data(tmp);
	}
	close(prog->fd);
	return (0);
}
