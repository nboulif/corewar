/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:34:34 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/17 21:45:40 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
#include <stdio.h>
#include "libft/libft.h"

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
	while (++i < 16)
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
	line->label = label;
	line->val_param[0] = 0;
	line->val_param[1] = 0;
	line->val_param[2] = 0;
	return (line);
}

int parse_params (t_data *line)
{
	int		i;
	char	*tmp;

	i = -1;
	while (++i < line->op->nb_params)
	{
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
				return (printf("error\n"));
			line->codage_octal |= REG_CODE << (2 * (3 - i));
		}
		else if (line->params[i][0] == '-' || ft_isdigit(line->params[i][0]))
		{
			line->val_param[i] = ft_atoi(line->params[i]);
			line->params[i] += count_digit(line->val_param[i]);
			line->codage_octal |= REG_CODE << (2 * (3 - i));
		}
		else
			return (printf("error\n"));
		line->params[i] = skip_chars(line->params[i], " \t");
		if (line->params[i])
			return (printf("error\n"));
		line->params[i] = tmp;
	}	
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
	while (line[i] != ':' && line[i] != '%' && line[i])
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
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '%')
		i++;
	opc = ft_strsub(line, 0, i);
	if (line[i] != '%')
		line = line + i + 1;
	else
		line = line + i;
	data = init_data(line, nb_line, label, opc);
	parse_params(data);
	return (data);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;
	t_prog	header;
	t_data	*data;
	t_data	*begin;

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
		printf("line %s\n", line);
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
	data = parse_commands(line, i++);
	begin = data;
	while (get_next_line(fd, &line) > 0)
	{
		if (!line)
			continue;
		data->next = parse_commands(line, i++);
		data = data->next;
	}
	close(fd);
	while (begin)
	{
		printf("nb_line: %d\n", begin->nb_line);
		printf("label: %s\n", begin->label);
		printf("val_param0:  %d\n", begin->val_param[0]);
		printf("val_param1:  %d\n", begin->val_param[1]);
		printf("val_param2:  %d\n", begin->val_param[2]);
		printf("codage octal %x\n", begin->codage_octal);
		printf("\n");
		begin = begin->next;
	}
	return (0);
}
