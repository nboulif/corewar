/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/10/16 16:46:59 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		manage_errors_header(t_prog *prog, int i)
{
	if (!ft_strncmp(prog->full_line + i, NAME_CMD_STRING, 5))
		return (print_error_tokken(prog, i, 5, "COMMAND_NAME"));
	else if (!ft_strncmp(prog->full_line + i, COMMENT_CMD_STRING, 8))
		return (print_error_tokken(prog, i, 8, "COMMAND_COMMENT"));
	else
		return (print_error_lexical(prog, i));
}

int		manage_errors_direct(t_prog *prog, int i, int o)
{
	int label;

	label = 0;
	if (*(prog->full_line + i + o) == ':')
	{
		label = 1;
		o++;
	}
	while (*(prog->full_line + i + o) && (ft_isalnum(*(prog->full_line + i + o)) || *(prog->full_line + i + o) == '_'))
		o++;
	if (label)
		return (print_error(prog, i, o, "DIRECT_LABEL"));
	return (print_error(prog, i, o, "DIRECT"));
}

int		manage_errors_instruction(t_prog *prog, int i, int o)
{
	int is_upper;

	is_upper = 0;
	while (*(prog->full_line + i + o) && (ft_isalnum(*(prog->full_line + i + o)) || *(prog->full_line + i + o) == '_'))
	{
		if (*(prog->full_line + i + o) >= 'A' && *(prog->full_line + i + o) <= 'Z')
			is_upper = 1;
		o++;
	}
	if (is_upper)
		return (print_error_lexical(prog, i));
	if (*(prog->full_line + i + o) && *(prog->full_line + i + o) == ':')
		return (print_error(prog, i, ++o, "LABEL"));
	o += (int)(skip_chars(prog->full_line + i + o, " \t") - (prog->full_line + i + o));
	if (!*(prog->full_line + i + o) || *(prog->full_line + i + o) == ' ' ||
		*(prog->full_line + i + o) == '\t' || *(prog->full_line + i + o) == SEPARATOR_CHAR)
		return (print_error(prog, i, o, "INSTRUCTION"));
	return (print_error_lexical(prog, i + o));
}

int		manage_errors_alnum(t_prog *prog, int i, int o)
{
	if (*(prog->full_line + i) == 'r')
	{
		if (*(prog->full_line + i + o) && ft_isdigit(*(prog->full_line + i + o)))
			o++;
		if (*(prog->full_line + i + o) && ft_isdigit(*(prog->full_line + i + o)))
			o++;
		if (!*(prog->full_line + i + o) || *(prog->full_line + i + o) == ' ' || *(prog->full_line + i + o) == '\t')
			return (print_error(prog, i, o, "REGISTER"));
		else
			return (manage_errors_instruction(prog, i, o));
	}
	else if (ft_isdigit(*(prog->full_line + i)))
	{
		while (*(prog->full_line + i + o) && ft_isdigit(*(prog->full_line + i + o)))
			o++;
		if (!*(prog->full_line + i + o) || *(prog->full_line + i + o) == ' ' || *(prog->full_line + i + o) == '\t')
			return (print_error(prog, i, o, "INDIRECT"));
		else
			return (manage_errors_instruction(prog, i, o));
	}
	else
		return (manage_errors_instruction(prog, i, o));
}

int		manage_errors_label(t_prog *prog, int i, int o)
{
	while (*(prog->full_line + i + o) && (ft_isalnum(*(prog->full_line + i + o)) || *(prog->full_line + i + o) == '_'))
		o++;
	return (print_error(prog, i, o, "INDIRECT_LABEL"));
}

int		manage_errors(t_prog *prog, int i)
{
	int o;

	o = 1;
	if (!*(prog->full_line + i))
		// printf("Syntax error at token [TOKEN][%0.3d:%0.3d] ENDLINE",
		// 	prog->nb_line, i);
		return (print_error(prog, i, 0, "ENDLINE"));
	else if (*(prog->full_line + i) == '"')
		return (printf("String ERRROROROROR\n"));
	else if (*(prog->full_line + i) == '.')
		return (manage_errors_header(prog, i));
	else if (*(prog->full_line + i) == ':')
		return (manage_errors_label(prog, i, o));
	else if (*(prog->full_line + i) == '%' && (*(prog->full_line + i + o) == ':' || ft_isdigit(*(prog->full_line + i + o))))
		return (manage_errors_direct(prog, i, o));
	else if (ft_isalnum(*(prog->full_line + i)))
		return (manage_errors_alnum(prog, i, o));
	else
		return (print_error_lexical(prog, i));
}

int		manage_errors_inexisting_label(t_prog *prog)
{
	(void)prog->name;
	printf("%d\n", prog->list_data->nb_line);
	printf("label error\n");
	return (0);
}
