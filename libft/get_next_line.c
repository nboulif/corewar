/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 21:45:47 by nsondag           #+#    #+#             */
/*   Updated: 2018/09/06 14:20:21 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	error(const int fd, char **line)
{
	if (fd < 0 || !line || fd > OPEN_MAX)
		return (1);
	return (0);
}

/*
** if no newline found return 2
** if newline found return 1
** if nothing too read return 0
*/

static int	reader(int fd, char *current_line, char next_line[BUFF_SIZE + 1])
{
	int i;
	int j;
	int ret;

	ft_bzero(current_line, BUFF_SIZE + 1);
	ft_bzero(next_line, BUFF_SIZE + 1);
	if ((ret = read(fd, current_line, BUFF_SIZE)) > 0)
	{
		i = 0;
		j = 0;
		while (current_line[i] != '\n' && current_line[i])
			i++;
		if (current_line[i] == '\n')
		{
			current_line[i] = '\0';
			while (current_line[i + 1])
				next_line[j++] = current_line[i++ + 1];
			return (1);
		}
	}
	if (ret == 0)
		return (0);
	return (2);
}

static void	join_and_free(char **line, char current_line[BUFF_SIZE + 1])
{
	char *tmp;

	tmp = *line;
	*line = ft_strjoin(*line, current_line);
	free(tmp);
}

int			get_next_line(const int fd, char **line)
{
	char		current_line[BUFF_SIZE + 1];
	static char next_line[BUFF_SIZE + 1];
	int			i;
	int			j;
	int			ret;

	i = 0;
	if (error(fd, line) || read(fd, current_line, 0))
		return (-1);
	while (next_line[i] != '\n' && next_line[i])
		i++;
	*line = ft_strsub(next_line, 0, i);
	if (next_line[i] == '\n')
	{
		j = -1;
		while (next_line[++j])
			next_line[j] = next_line[j + i + 1];
		return (1);
	}
	while ((ret = reader(fd, current_line, next_line)) == 2)
		join_and_free(line, current_line);
	join_and_free(line, current_line);
	if (!ft_strlen(*line) && !ret)
		return (0);
	return (1);
}
