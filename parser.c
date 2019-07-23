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
#include <libft/libft.h>

int find_name(char *line)
{
	return (1);
}

int find_comment(char *line)
{
	return (1);
}

int main(int argc, char **argv)
{
	int fd;
	char line;
	int i;

	if (argc < 2)
		return (printf("print usage\n"));
	fd = open(argv[1], O_RDONLY);
	i = 0;
	while (get_next_line(fd, char *line) > 0)
	{
			if (!find_name(*line))
			{
				close(fd);
				return (printf("print error name not found"));
			}
		if (i == 1)
	}
	if (!find_comment(*line))
		return (printf("print error coomment not found"));
		parse_commands(*line);
}
