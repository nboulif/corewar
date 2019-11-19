/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/06 17:10:41 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*err_msgs[19] =
{
	"",
	"Malloc error (%s) on line : %d\n",
	"Can't identify operation code on line %d : %s\n",
	"",
	"Wrong number of arguments : %d\n",
	"Can't read source file %s\n",
	"Missing label : %s\n",
	"Unknown command : %s\n",
	"Double %s on line %d.\n",
	"Empty %s on line %d\n",
	"Missig %s quote for %s on line %d.\n",
	"Max length exceeded for %s on line %d : %d (max: %d)\n",
	"Lexical error (%d) on [%0.3d:%0.3d].\n",
	"Invalid register number on line %d : r%d \n",
	"Invalid value (\"%s\") of type %s on line %d, param number %d.\n",
	"Empty param number %d on line %d.\n",
	"Wrong number of params on line %d : %d vs %d\n",
	"Invalid param on line %d.\nReceived %s type for the param number %d\n",
	"Command in program at [%0.3d:%0.3d].",
};

int		err_default(t_prog *p, int error_nb)
{
	return (printf(err_msgs[error_nb], p->nb_line, p->i));
}

int		err_lexical(t_prog *p, int error_nb, int i)
{
	return (printf(err_msgs[ERROR_LEXICAL], error_nb, p->nb_line, i));
}

int		err_malloc(char *str, int nb_line)
{
	return (printf(err_msgs[ERROR_MALOC], str, nb_line));
}

int		err_param_type(t_prog *p, char *str, int indice)
{
	return (printf(err_msgs[ERROR_PARAM_TYPE], p->nb_line, str, indice));
}

int		err_missing_quotes(t_prog *p, char *error_type, int start)
{
	if (start)
		return (printf(err_msgs[ERROR_MISSING_QUOTE],
			"start", error_type, p->nb_line));
	else
		return (printf(err_msgs[ERROR_MISSING_QUOTE],
			"end", error_type, p->nb_line));
}

int		err_header_divers(t_prog *p, int error_nb, char *error_type)
{
	return (printf(err_msgs[error_nb], error_type, p->nb_line));
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
			NO_LABEL, &error_label[2], DEREF,
			error_line, i - j - 1, error_label);
	return (1);
}
