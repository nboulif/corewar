/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/22 19:10:30 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int manage_errors_direct(t_prog *prog, int i, int o)
{
	if (*(prog->line + i + o) == ':')
		o++;
	while (*(prog->line + i + o) && (ft_isalnum(*(prog->line + i + o)) || *(prog->line + i + o) == '_'))
		o++;
	if (*(prog->line + i + o) == ':')
		return (print_error(prog, i, o, "DIRECT_LABEL"));
	return (print_error(prog, i, o, "DIRECT"));
}

int manage_errors_instruction(t_prog *prog, int i, int o)
{
	while (*(prog->line + i + o) && (ft_isalnum(*(prog->line + i + o)) || *(prog->line + i + o) == '_'))
		o++;
	return (print_error(prog, i, o, "INSTRUCTION"));
}

int manage_errors_header(t_prog *prog, int i)
{
	if (!ft_strncmp(prog->line + i, NAME_CMD_STRING, 5))
		return (print_error_tokken(prog, i, 5, "COMMAND_NAME"));
	else if (!ft_strncmp(prog->line + i, COMMENT_CMD_STRING, 8))
		return (print_error_tokken(prog, i, 8, "COMMAND_COMMENT"));
	else
		return (print_error_lexical(prog, i));
}

int manage_errors_alnum(t_prog *prog, int i, int o)
{
	if (*(prog->line + i) == 'r')
	{
		if (*(prog->line + i + o) && ft_isdigit(*(prog->line + i + o)))
			o++;
		if (*(prog->line + i + o) && ft_isdigit(*(prog->line + i + o)))
			o++;
		return (print_error(prog, i, o, "REGISTER"));
	}
	else if (ft_isdigit(*(prog->line + i)))
	{
		while (*(prog->line + i + o) && ft_isdigit(*(prog->line + i + o)))
			o++;
		if (!*(prog->line + i + o) || *(prog->line + i + o) == ' ' || *(prog->line + i + o) == '\t')
			return (print_error(prog, i, o, "INDIRECT"));
		else
			return (manage_errors_instruction(prog, i, o));
	}
	else
		return (manage_errors_instruction(prog, i, o));
}

int manage_errors(t_prog *prog, int i)
{
	int o;

	o = 1;
	if (*(prog->line + i) == '"')
		return (printf("String ERRROROROROR\n"));
	else if (*(prog->line + i) == '.')
		return (manage_errors_header(prog, i));
	else if (*(prog->line + i) == '%')
		return (manage_errors_instruction(prog, i, o));
	else if (ft_isalnum(*(prog->line + i)))
		return (manage_errors_alnum(prog, i, o));
	return (printf("ERRROROROROR"));
}