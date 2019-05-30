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

int		ft_count_words_2(char const *s)
{
	int i;

	i = *s && *s != ' ' && *s != '\t' ? 1 : 0;
	while (*s)
	{
		if ((*s == ' ' || *s == '\t') && *(s + 1) != ' ' && *(s + 1) != '\t' && *(s + 1))
			i++;
		s++;
	}
	return (i);
}

char		**ft_strsplit_2(char const *s)
{
	char		**tab;
	size_t		i;
	size_t		d;
	size_t		count_words;

	if (!s || !(tab =
		(char **)malloc(sizeof(char *) * (ft_count_words_2(s) + 1))))
		return (NULL);
	i = 0;
	count_words = ft_count_words_2(s);
	while (i < count_words)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		d = 0;
		while (*(s + d) && *(s + d) !=  ' ' && *(s + d) !=  '\t')
			d++;
		if (!(ft_tabadd_sec(&tab, i, d)))
			return (NULL);
		tab[i] = ft_strncpy(tab[i], s, d);
		s += d;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

int check_if_operation(char *line)
{
	int i;

	i = 0;
	while (i < 16)
		if (ft_strstr(line, g_op_tab[i++].name))
			return (1);
	return (0);
	
}

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
			{

				// ft_putendl(line);
				
				char 	**line_splited;
				int i;
				
				line_splited = ft_strsplit_2(line);

				// t_inst 	*cur_instruction;
				i = 0;
				while (line_splited && line_splited[i])
				{	
					
					if (check_if_operation(line_splited[i]))
					{
						ft_putendl(line_splited[i]);	
					}
					i++;
					
				}
				// ft_tabdel(&line_splited);
			}
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