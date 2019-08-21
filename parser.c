/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:34:34 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/21 18:15:18 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int	find_name(char *line, t_prog *header)
{
	int name_length;
	int i;
	int test;

	i = 0;
	name_length = ft_strlen(NAME_CMD_STRING);
	if ((test = ft_strncmp(NAME_CMD_STRING, line, name_length)) != 0)
		return (0);
	if (line[i + name_length + 1] == '"')
		i++;
	while (line[i + name_length + 1] != '"')
	{
		header->name[i - 1] = line[i + name_length + 1];
		i++;
	}
	printf("%s\n", header->name);
	return (1);
}

int	find_comment(char *line, t_prog *header)
{
	int	comment_length;
	int i;
	int test;

	i = 0;
	comment_length = strlen(COMMENT_CMD_STRING);
	if ((test = ft_strncmp(COMMENT_CMD_STRING, line, comment_length)) != 0)
		return (0);
	if (line[i + comment_length + 1] == '"')
		i++;
	while (line[i + comment_length + 1] != '"')
	{
		header->comment[i - 1] = line[i + comment_length + 1];
		i++;
	}
	printf("%s\n", header->comment);
	magic_number(header);
	return (1);
}

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

t_data	*init_data(char *str_params, int nb_line, char *label, char *str_opc)
{
	t_data	*line;

	if (!(line = (t_data*)malloc(sizeof(t_data))))
		return (NULL);
	if (!(line->op = identify_opc(str_opc)))
		return (NULL);
	line->codage_octal = 0;
	line->params = ft_strsplit(str_params, SEPARATOR_CHAR);
	line->next = NULL;
	line->nb_line = nb_line;
	line->val_param[0] = 0;
	line->val_param[1] = 0;
	line->val_param[2] = 0;
	line->nb_octet = 0;
	if (label && *label)
		line->label = label;
	else
		line->label = NULL;
	return (line);
}

int parse_params (t_data *line)
{
	int		i;
	char	*tmp;


	printf("parse_params\n");
	i = -1;
	if (line->op->codage_octal)
		line->nb_octet++;
	printf("operation %s\n", line->op->name);
	while (++i < line->op->nb_params)
	{
		printf("line_params %s\n", line->params[i]);
		line->params[i] = skip_chars(line->params[i], " \t");
		tmp = line->params[i];
		if (!line->params[i])
			return (printf("error1\n"));
		if (line->params[i][0] == 'r')
		{
			line->val_param[i] = ft_atoi(&line->params[i][1]);
			if (!(line->val_param[i] > 0 && line->val_param[i] < 17  && (line->op->params[i] & T_REG)))
				return (printf("error2\n"));
			line->params[i] += count_digit(line->val_param[i]) + 1;
			line->codage_octal |= REG_CODE << (2 * (3 - i));
			line->nb_octet++;
		}
		else if (line->params[i][0] == DIRECT_CHAR)
		{
			if (line->params[i][1] == LABEL_CHAR)
				line->params[i] = skip_chars(&line->params[i][2], LABEL_CHARS);
			else if (line->params[i][1] == '-' || ft_isdigit(line->params[i][1]))
			{
				line->val_param[i] = ft_atoi(&line->params[i][1]);
				line->params[i] += count_digit(line->val_param[i]) + 1;
			}
			else
				return (printf("error3\n"));
			line->codage_octal |= DIR_CODE << (2 * (3 - i));
			if (line->op->dir_size == 1)
			{
				printf("2 octets\n");
				line->nb_octet += 2;
			}
			else
			{
				printf("4 octets\n");
				line->nb_octet += 4;
			}
		}
		else if (line->params[i][0] == '-' || ft_isdigit(line->params[i][0]))
		{
			line->val_param[i] = ft_atoi(line->params[i]);
			line->params[i] += count_digit(line->val_param[i]);
			line->codage_octal |= IND_CODE << (2 * (3 - i));
			line->nb_octet += 2;
		}
		else
			return (printf("error4\n"));
		line->params[i] = skip_chars(line->params[i], " \t");
		if (line->params[i] && line->params[i][0] && line->params[i][0] != '#')
			return (printf("error5 %s\n", line->params[i]));
		line->params[i] = tmp;
	}
	line->nb_octet++;
	return (0);
}

t_data	*parse_commands(char *line, int nb_line)
{
	char	*opc;
	char	*label;
	t_data	*data;
	int		i;

	label = "";
	line = skip_chars(line, " \t");
	i = 0;
	while (line[i] && line[i] != ':' && line[i] != '%' && line[i] != ' ' && line[i] != '\t')
		i++;
	if (!line[i])
		return (NULL);
	if (line[i] == ':')
	{
		label = ft_strsub(line, 0, i);
		while (line[i + 1] == ' ' || line[i + 1] == '\t')
			i++;
		line = line + i + 1;
	}
	i = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && line[i] != '%')
		i++;
	//if (!line[i])
	//{
	//	printf("yy\n");
	//	return(NULL); 
	//}
	opc = ft_strsub(line, 0, i);
	printf("opc *%s*\n", opc);
	printf("tt\n");
	printf("liiiine **%s** *%c*\n", line, line[i]);
	if (line[i] && line[i] != '%')
		line = line + i + 1;
	else
		line = line + i;
	printf("Liiiine **%s** *%c*\n", line, line[0]);
	data = NULL;
	//if (line[i] != '%')
		data = init_data(line, nb_line, label, opc);
	printf("line[i] %c\n", line[0]);
	if	(*line)
	{
		parse_params(data);
		printf("nb_oct %d\n", data->nb_octet);
	}
	return (data);
}

t_label *update_list_label(t_label *list_label, t_data *data, t_label **begin_label)
{
	t_label *new;


	if (data->label)
	{	
		new = (t_label *)malloc(sizeof(t_label));
		new->label = data->label;
		new->pc = data->pc;
		new->next = NULL;
		if (list_label)
			list_label->next = new;
		if (!*begin_label)
			*begin_label = new;
		return (new);
	}
	return (list_label);	
}


int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;
	t_prog		header;
	t_data	*data;
	t_data	*begin;
	t_label *list_label;
	t_label *begin_label;
	t_data	*tmp;

	list_label = NULL;
	begin_label = NULL;
	begin = NULL;
	header.name = ft_strnew(PROG_NAME_LENGTH);
	header.comment = ft_strnew(COMMENT_LENGTH);
	line = (char *)malloc(sizeof(*line) * 1);
	if (argc < 2)
		return (printf("print usage\n"));
	fd = open(argv[1], O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		i++;
		line = skip_chars(line, " \t");
		printf("i: %d line %s\n", i, line);
		if (!line)
			continue;
		else if (*line == '.' || *line == '#' || !*line)
		{
			if (find_name(line, &header))
				continue;
			if (find_comment(line, &header))
				continue;
		}
		else
			break;
		printf("test\n");
	}
	data = parse_commands(line, i);
	data->pc = 0;
	if (data->label)
		list_label = update_list_label(list_label, data, &begin_label);
	else
		begin = data;
	while (get_next_line(fd, &line) > 0)
	{
		i++;
		printf("------------------------------------\n");
		line = skip_chars(line, " \t");
		if (!line || *line == '#' || !*line)
			continue;
		tmp = parse_commands(line, i);
		tmp->pc = data->pc + data->nb_octet;
		if (tmp->op->opc)
		{
			if (!begin)
				begin = tmp;
			printf("op\n");
			data->next = tmp;
			data->next->pc = data->pc + data->nb_octet;
			printf("octet %d\n", data->nb_octet);
			data = data->next;
			printf("PC %d\n", data->pc);
		}
		if (tmp->label)
		{
			printf("label PC %d\n", tmp->pc);
			list_label = update_list_label(list_label, tmp, &begin_label);
			printf("label\n");
		}
		printf("i: %d line: %s\n", i, line);
	}
	close(fd);
	while (begin)
	{
		printf("nb_line: %d\n", begin->nb_line);
		printf("label: %s\n", begin->label);
		printf("val_param0:  %d\n", begin->val_param[0]);
		printf("val_param1:  %d\n", begin->val_param[1]);
		printf("val_param2:  %d\n", begin->val_param[2]);
		printf("codage octal %d\n", begin->codage_octal);
		printf("\n");
		begin = begin->next;
	}
	while (begin_label)
	{
		printf("label: %s\n", begin_label->label);
		printf("pc: %d\n", begin_label->pc);
		begin_label = begin_label->next;
	}
	return (0);
}
