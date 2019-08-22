/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/22 19:10:30 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	find_name(t_prog *prog)
{
	int name_length;
	int i;

	i = 0;
	name_length = ft_strlen(NAME_CMD_STRING);
	if ((ft_strncmp(NAME_CMD_STRING, prog->line, name_length)) != 0)
		return (0);
	if (prog->line[i + name_length + 1] == '"')
		i++;
	while (prog->line[i + name_length + 1] != '"')
	{
		prog->name[i - 1] = prog->line[i + name_length + 1];
		i++;
	}
	prog->name_found = 1;
	return (1);
}

static int	find_comment(t_prog *prog)
{
	int	comment_length;
	int i;

	i = 0;
	comment_length = strlen(COMMENT_CMD_STRING);
	if ((ft_strncmp(COMMENT_CMD_STRING, prog->line, comment_length)) != 0)
		return (0);
	if (prog->line[i + comment_length + 1] == '"')
		i++;
	while (prog->line[i + comment_length + 1] != '"')
	{
		prog->comment[i - 1] = prog->line[i + comment_length + 1];
		i++;
	}
	prog->comment_found = 1;
	return (1);
}

t_prog		*get_header(t_prog *prog)
{
	if (!(prog->name = ft_strnew(PROG_NAME_LENGTH)))
		return (NULL);
	if (!(prog->comment = ft_strnew(COMMENT_LENGTH)))
		return (NULL);
	while (get_next_line(prog->fd, &prog->line) > 0)
	{
		prog->nb_line++;
		prog->line = skip_chars(prog->line, " \t");
		if (!prog->line || !*prog->line || *prog->line == '#')
			continue;
		else if (*prog->line == '.')
		{
			if (!prog->name_found && find_name(prog))
				continue;
			if (!prog->comment_found && find_comment(prog))
				continue;
			else
				printf("Error\n");
		}
		else
			break ;
	}
	return (prog);
}
