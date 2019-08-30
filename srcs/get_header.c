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


int get_valid_name_comment_loop(t_prog *prog, int max_lenght, char **final_line, int i)
{
	int z;

	while (prog->l_h < max_lenght)
	{
		z = 0;
		while (*(prog->line + i + z) && *(prog->line + i + z) != '"')
			z++;
		if (prog->l_h + z >= max_lenght)
			return (printf("Champion name too long (Max length %d)\n", max_lenght));
		ft_strncpy((*final_line) + prog->l_h, prog->line + i, z);
		prog->l_h += z;
		if (!*(prog->line + i++ + z))
		{
			if (get_next_line(prog->fd, &prog->line) <= 0)
				return (printf("NO MORE LINE OR PROBLEM READING\n"));
			i = 0;
			(*final_line)[prog->l_h++] = '\n';
			prog->nb_line++;
		}
		else
		{
			i += (int)(skip_chars(prog->line + i + z, " \t") - (prog->line + i + z));
			return (!*(prog->line + i + z) ? 0 : manage_errors(prog, i + z));
		}
	}
	return (printf("Champion name too long (Max length %d)\n", max_lenght));
}

int get_valid_name_comment(t_prog *prog, int max_lenght, char **final_line)
{
	int i;
	
	i = max_lenght == PROG_NAME_LENGTH ? 5 : 8;
	i += (int)(skip_chars(prog->line + i, " \t") - (prog->line + i));
	if (*(prog->line + i) != '"')
		return (print_error_tokken(prog, i, 0, "ENDLINE"));
	i++;
	if (!( (*final_line) = ft_strnew(max_lenght)))
		return (printf("MALLOC PROBLEM\n"));
	prog->l_h = 0;
	return (get_valid_name_comment_loop(prog, max_lenght, final_line, i));
}

int get_header(t_prog *prog)
{
	while (get_next_line(prog->fd, &prog->line) > 0)
	{
		prog->nb_line++;
		prog->line = skip_chars(prog->line, " \t");
		if (!prog->line || !*prog->line || *prog->line == '#')
			continue;
		else if (!ft_strncmp(prog->line, NAME_CMD_STRING, 5))
		{	
			if (prog->name)
				return (print_error_tokken(prog, 0, 5, "COMMAND_NAME"));
			else if (get_valid_name_comment(prog, PROG_NAME_LENGTH, &prog->name))
				return (1);
		}
		else if (!ft_strncmp(prog->line, COMMENT_CMD_STRING, 8))
		{
			if (prog->comment)
				return (print_error_tokken(prog, 0, 5, "COMMAND_COMMENT"));
			else if (get_valid_name_comment(prog, COMMENT_LENGTH, &prog->comment))
				return (1);
		}
		else
			return (manage_errors(prog, 0));
		if (prog->name && prog->comment)
			return (0);
	}
	return (1);
}
