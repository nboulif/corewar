/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:25:24 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/06 16:40:42 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				tab_len(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

t_data			*get_pc(t_prog *prog, t_data *tmp_data, t_data *data)
{
	tmp_data->pc = data->pc + data->nb_octet;
	(!prog->list_data) ? prog->list_data = tmp_data : 0;
	data->next = tmp_data;
	if (tmp_data->op && tmp_data->op->opc)
		data->next->pc = data->pc + data->nb_octet;
	data->nb_line = prog->nb_line;
	return (data);
}

t_op			*identify_opc(char *line)
{
	int i;

	i = -1;
	if (!*line)
		return (&g_op_tab[16]);
	while (++i < 16)
	{
		if (!ft_strcmp(line, g_op_tab[i].name))
			return (&g_op_tab[i]);
	}
	return (NULL);
}
