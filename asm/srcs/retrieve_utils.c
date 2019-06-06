/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   retrieve_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char		*retrieve_valid_word(char *param)
{
	int y;

	y = 1;
	while(ft_strchr(LABEL_CHARS, *(param + y)))
		y++;
	if (!y)
	{
		ft_putendl("ERROR 872");
		return (NULL);
	}
	return (ft_strsub(param, 1, y - 1));
}

t_inst		*check_and_retrieve_valid_inst(t_asm *u, char *word)
{
	t_inst		*tmp_inst;

	tmp_inst = u->prog->insts;
	while (tmp_inst && ft_strcmp(tmp_inst->name, word))
			tmp_inst = tmp_inst->next;
		
	if (!tmp_inst)
	{
		ft_putendl("ERROR 873");
		return (NULL);
	}
	return (tmp_inst);
}

char			*retrieve_next_world(char **line)
{
	char		*word;
	int			i;
	
	i = 0;
	(*line) = zap_space_tab(*line);

	while (*((*line) + i))
	{
		if (!ft_strchr(LABEL_CHARS, *((*line) + i)))
			break ;
		i++;
	}
	
	if (i == 0)
		return (NULL);
	word = ft_strsub((*line), 0, i);
	(*line) += i; 
	return (word);

}
