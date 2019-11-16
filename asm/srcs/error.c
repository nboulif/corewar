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
