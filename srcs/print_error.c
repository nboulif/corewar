/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/22 19:10:30 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int print_error_lexical(t_prog *prog, int i)
{
	return (printf("Lexical error at [%d:%d]\n", prog->nb_line, i + 1));
}

int print_error_tokken(t_prog *prog, int i, int o, char *error_type)
{
	printf("Syntax error at token [TOKEN][%0.3d:%0.3d] %s",
					   prog->nb_line, i + 1, error_type);
	if (o)
		printf(" \"%.*s\"", o, prog->line + i);
	printf("\n");
	return (1);
}

int print_error(t_prog *prog, int i, int o, char *error_type)
{
	if (*(prog->line + i + o + (int)(skip_chars(prog->line + i + o, " \t") - (prog->line + i + o))))
		return (print_error_lexical(prog, 1 + i + o + (int)(skip_chars(prog->line + i + o, " \t") - (prog->line + i + o))));
	else
		return (print_error_tokken(prog, i, o, error_type));
}