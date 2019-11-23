/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/06 17:10:41 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		err_default(t_prog *p, int error_nb)
{
	return (printf(g_err_msgs[error_nb], p->nb_line, p->i));
}

int		err_lexical(t_prog *p, int error_nb, int i)
{
	return (printf(g_err_msgs[ERROR_LEXICAL], error_nb, p->nb_line, i));
}

int		err_malloc(char *str, int nb_line)
{
	return (printf(g_err_msgs[ERROR_MALLOC], str, nb_line));
}

int		err_param_type(t_prog *p, char *str, int indice)
{
	return (printf(g_err_msgs[ERROR_PARAM_TYPE], p->nb_line, str, indice));
}

int		err_missing_quotes(t_prog *p, char *error_type, int start)
{
	if (start)
		return (printf(g_err_msgs[ERROR_MISSING_QUOTE],
			"start", error_type, p->nb_line));
	else
		return (printf(g_err_msgs[ERROR_MISSING_QUOTE],
			"end", error_type, p->nb_line));
}
