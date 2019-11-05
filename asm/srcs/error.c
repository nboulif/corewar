/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/05 19:48:56 by nsondag          ###   ########.fr       */
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
	o += (int)(skip_chars2(prog->full_line + i + o, " \t") - (prog->full_line + i + o));
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
	if (!*(prog->line + i))
		// printf("Syntax error at token [TOKEN][%0.3d:%0.3d] ENDLINE",
		// 	prog->nb_line, i);
		return (print_error(prog, i, 0, "ENDLINE"));
	else if (*(prog->line + i) == '"')
		return (printf("String ERRROROROROR\n"));
	else if (*(prog->line + i) == '.')
		return (manage_errors_header(prog, i));
	else if (*(prog->line + i) == ':')
		return (manage_errors_label(prog, i, o));
	else if (*(prog->line + i) == '%' && (*(prog->line + i + o) == ':' || ft_isdigit(*(prog->line + i + o))))
		return (manage_errors_direct(prog, i, o));
	else if (ft_isalnum(*(prog->line + i)))
		return (manage_errors_alnum(prog, i, o));
	else
		return (print_error_lexical(prog, i));
}

int		manage_errors_inexisting_label(t_data *data, int error_line)
{
	int		i;
	int		j;
	char	*error_label;

	i = data->nb_line;
	while (data->nb_line != error_line)
		data = data->next;
	j = 0;
	i = 0;
	while (data->line[i] != '%')
		i++;
	i += 2;
	while (data->line[i] != ',' && data->line[i] != ' ' && data->line[i])
	{
		i++;
		j++;
	}
	error_label = ft_strsub(data->line, i - j - 2, j + 2);
	printf("%s %s %s [TOKEN][%0.3d:%0.3d] DIRECT_LABEL \"%s\"\n",
			NO_LABEL, &error_label[2], DEREF, error_line, i - j - 1, error_label);
	return (1);
}
