/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:34:34 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/14 20:03:35 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
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

int	identify_opc(char *line)
{
	char	**opc;
	int		i;

	opc = malloc(sizeof(char*) * 16);
	*opc = malloc(sizeof(char*) * 5);
	//en fait il y a deja un tableau 
	opc[0] = "live";
	opc[1] = "ld";
	opc[2] = "st";
	opc[3] = "add";
	opc[4] = "sub";
	opc[5] = "and";
	opc[6] = "or";
	opc[7] = "xor";
	opc[8] = "zjmp";
	opc[9] = "ldi";
	opc[10] = "sti";
	opc[11] = "fork";
	opc[12] = "lld";
	opc[13] = "lldi";
	opc[14] = "lfork";
	opc[15] = "aff";
	i = 0;
	while (++i < 16)
	{
		if (!ft_strcmp(line, opc[i - 1]))
			return (i);
	}
	return (0);
}

int parse_params (char *str_params, t_op op)
{
	char	**params;
	int		i;
	int		reg;
	char	*str_direct;
	int		direct;
	int 	indirect;
	int		code_octal;

	i = 0;
	code_octal = 0;
	params = ft_strsplit(str_params, SEPARATOR_CHAR);
	while (i < op.nb_params)
	{
		params[i] = skip_chars(params[i], " \t");
		if (!params[i])
			return (printf("error\n"));
		if (params[i][0] == 'r')
		{
			reg = ft_atoi(&params[i][1]);
			if (!(reg > 0 && reg < 17  && (op.params[i - 1] & T_REG)))
				return (printf("error\n"));
			params[i] += count_digit(reg) + 1;
			code_octal |= REG_CODE << (2 * (3 - i));
		}
		else if (params[i][0] == DIRECT_CHAR)
		{
			if (params[i][1] == LABEL_CHAR)
			{
				str_direct = &params[i][2];
				params[i] = skip_chars(&params[i][2], LABEL_CHARS);
			}
			else if (params[i][1] == '-' || ft_isdigit(params[i][1]))
			{
				direct = ft_atoi(&params[i][1]);
				params[i] += count_digit(direct) + 1;
			}
			else
				return (printf("error\n"));
			code_octal |= REG_CODE << (2 * (3 - i));
		}
		else if (params[i][0] == '-' || ft_isdigit(params[i][0]))
		{
			indirect = ft_atoi(params[i]);
			params[i] += count_digit(indirect);
			code_octal |= REG_CODE << (2 * (3 - i));
		}
		else
			return (printf("error\n"));
		params[i] = skip_chars(params[i], " \t");
		if (params[i])
			return (printf("error\n"));
	}	
	return (0);
}

int	parse_commands(char *line)
{
	char	*opc;
	int		i;
	t_line	a;

	a.label = "";
	line = skip_chars(line, " \t");
	i = 0;
	while (line[i] != ':' && line[i] != '%' && line[i])
		i++;
	if (!line[i])
		return (0);
	if (line[i] == ':')
	{
		a.label = ft_strnew(i);
		a.label = ft_strsub(line, 0, i);
		while (line[i + 1] == ' ' || line[i + 1] == '\t')
			i++;
		line = line + i + 1;
	}
	i = 0;
	while (line[i] != ' ' && line[i] != '\t' && line[i] != '%')
		i++;
	opc = ft_strnew(i);
	opc = ft_strsub(line, 0, i);
	a.opc = identify_opc(opc);
	if (line[i] != '%')
		line = line + i + 1;
	else
		line = line + i;
	a.params = line;
	parse_params(line, a.opc);
	printf("opc %d\n", a.opc);
	printf("label %s\n", a.label);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		i;
	t_prog	header;

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
		if (find_name(line, &header))
			continue;
		if (find_comment(line, &header))
			continue;
		parse_commands(line);
	}
	close(fd);
	return (0);
}
