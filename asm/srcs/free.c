/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 13:06:40 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/06 16:48:53 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		free_data_params(t_data *d, int i)
{
	int y;

	y = 0;
	while (y < i)
		free(d->params[y++]);
	free(d->params);
	return (0);
}

int		free_one_data(t_data *data)
{
	data->line ? free_str(data->line) : 0;
	data->label ? free_str(data->label) : 0;
	if (data->params)
		free_data_params(data, tab_len(data->params));
	free(data);
	return (0);
}

int		free_data(t_data *begin_data)
{
	t_data	*data;
	t_data	*tmp_data;

	data = begin_data;
	tmp_data = data;
	while (data)
	{
		tmp_data = data->next;
		free_one_data(data);
		data = tmp_data;
	}
	return (0);
}

int		free_prog(t_prog* p)
{


	p->name ? free_str(p->name) : 0;
	p->comment ? free_str(p->comment) : 0;
	p->line ? free_str(p->line) : 0;
	if (p->list_data)
		free_data(p->list_data);
	free(p);
	return (0);
}


int		free_str(char *str)
{
	free(str);
	return (0);
}
