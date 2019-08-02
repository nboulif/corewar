/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:34:34 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/02 19:57:56 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line.h"

int	find_name(char *line, t_prog *header)
{
	int name_length;
	int i;
	int test;

	i = 0;
	name_length = strlen(NAME_CMD_STRING);
	if ((test = strncmp(NAME_CMD_STRING, line, name_length)) != 0)
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
	if ((test = strncmp(COMMENT_CMD_STRING, line, comment_length)) != 0)
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
		if (!strcmp(line, opc[i - 1]))
			return (i);
	}
	return (0);
}

int	parse_commands(char *line)
{
	char	**arg;
	char	*opc;
	int		i;
	t_line	a;

	a.label = "";
	i = 0;
	printf("**line** %s\n", line);
	while (line[i] != ' ' && line[i] != ':' && line[i] != '%' && line[i] != ',')
		i++;
	printf("%c\n", line[i]);
	arg = ft_strsplit(line, ' ');
	if (arg[0] == NULL)
		return (0);
	i = 0;
	if (arg[i][ft_strlen(arg[i]) - 1] == ':')
		a.label = arg[i++];
	opc = arg[i++];
	a.params = arg[i];
	a.opc = identify_opc(opc);
	printf("label: %s\n", a.label);
	printf("opc: %d\n", a.opc);
	printf("params: %s\n", a.params);
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
		if (find_name(line, &header))
			continue;
		if (find_comment(line, &header))
			continue;
		parse_commands(line);
	}
	close(fd);
	return (0);
}
