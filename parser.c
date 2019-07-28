/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 18:34:34 by nsondag           #+#    #+#             */
/*   Updated: 2019/07/23 19:30:20 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "get_next_line.h"

int find_name(char *line)
{
	int name_length;
	int i;
	char *name;
	int test;

	name = ft_strnew(128);
	i = 0;
	name_length = strlen(NAME_CMD_STRING);
	if ((test = strncmp(NAME_CMD_STRING, line, name_length)) != 0)
		return (0);
	if (line[i + name_length + 1] == '"')
		i++;
	while (line[i + name_length + 1] != '"')
	{
		name[i - 1] = line[i + name_length + 1];
		i++;
	}
	printf("%s\n", name);
	return (1);
}

int find_comment(char *line)
{
	return (1);
}

int main(int argc, char **argv)
{
	int fd;
	char *line;
	int i;

	line = (char *)malloc(sizeof(*line) * 1);
	if (argc < 2)
		return (printf("print usage\n"));
	fd = open(argv[1], O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
			if (!find_name(line))
			{
				close(fd);
				return (printf("print error name not found\n"));

			}
		close(fd);
	}
	if (!find_comment(&line))
		return (printf("print error coomment not found\n"));
	//parse_commands(&line);
	return (0);
}
