/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_header.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/10/21 14:36:04 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		val_name_comment_loop(t_prog *p, int max_len, char **final_line, int i)
{
	int z;

	while (!(z = 0) && p->l_h < max_len)
	{
		while (*(p->line + i + z) && *(p->line + i + z) != '"')
			z++;
		if (p->l_h + z >= max_len)
			return (printf("%s (Max length %d)\n", LONG_NAME, max_len));
		ft_strncpy((*final_line) + p->l_h, p->line + i, z);
		p->l_h += z;
		if (!*(p->line + i++ + z))
		{
			if (get_next_line(p->fd, &p->line) <= 0)
				return (printf("NO MORE LINE OR PROBLEM READING\n"));
			i = 0;
			(*final_line)[p->l_h++] = '\n';
			p->nb_line++;
		}
		else
		{
			i += (int)(skip_chars(p->line + i + z, " \t") - (p->line + i + z));
			return (!*(p->line + i + z) ? 0 : manage_errors(p, i + z));
		}
	}
	return (printf("%s (Max length %d)\n", LONG_NAME, max_len));
}

int		get_valid_name_comment(t_prog *prog, int max_len, char **final_line)
{
	int i;

	i = max_len == PROG_NAME_LENGTH ? 5 : 8;
	i += (int)(skip_chars(prog->line + i, " \t") - (prog->line + i));
	if (!*(prog->line + i))
		return (print_error_tokken(prog, i, 0, "ENDLINE"));
	if (*(prog->line + i) != '"')
		return (manage_errors(prog, i));
	i++;
	if (!((*final_line) = ft_strnew(max_len)))
		return (printf("MALLOC PROBLEM\n"));
	prog->l_h = 0;
	return (val_name_comment_loop(prog, max_len, final_line, i));
}

int		get_header(t_prog *p)
{
	while ((p->nb_line++) >= 0 && get_next_line(p->fd, &p->full_line) > 0)
	{
		p->line = skip_chars(p->full_line, " \t");
		if (!p->line || !*p->line || *p->line == '#')
			continue;
		else if (!ft_strncmp(p->line, NAME_CMD_STRING, 5))
		{
			if (p->name)
				return (print_error_tokken(p, 0, 5, "COMMAND_NAME"));
			if (get_valid_name_comment(p, PROG_NAME_LENGTH, &p->name))
				return (1);
		}
		else if (!ft_strncmp(p->line, COMMENT_CMD_STRING, 8))
		{
			if (p->comment)
				return (print_error_tokken(p, 0, 5, "COMMAND_COMMENT"));
			if (get_valid_name_comment(p, COMMENT_LENGTH, &p->comment))
				return (1);
		}
		else
			return (manage_errors(p, 0));
		if (p->name && p->comment)
			return (0);
	}
	return (0);
}
