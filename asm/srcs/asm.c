/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int argc, char const *argv[])
{
	char		*line;
	t_asm		*u;
	int			res;
	int fd;

	if (argc != 2)
	{
		ft_putendl("WRONG NB PARAM");
		return (0);
	}

	fd = open(argv[1], O_RDONLY);
	u = (t_asm*)malloc(sizeof(t_asm));
	if (fd <= 0)
	{
		ft_putendl("ERROR OPEN FILE");
		return (0);
	}
	
	while ((res = get_next_line(fd, &line)) == 1)
	{
		if (line[0] == '#')
		{
			ft_strdel(&line);
			continue;
		}
		if (ft_strstr(line, ".name"))
			u->name = line;
		else if (ft_strstr(line, ".comment"))
			u->comment = line;
		else
		{
			if (*line)
				ft_putendl(line);
			
			ft_strdel(&line);
		}
	}
	if (res < 0)
	{
		ft_putendl("ERROR READ");
		return (0);
	}
	return (0);
}