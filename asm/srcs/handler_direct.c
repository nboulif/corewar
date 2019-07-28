/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_direct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			handle_direct_number(t_asm *u, t_op_ch *cur_op_ch, int nb)
{

	unsigned int	bytes;
	unsigned int	byte;

	if (nb >= 0)
		bytes = nb;
	else
		bytes = -1 + nb + 1;
	if (!cur_op_ch->op->dir_size)
	{
		byte = (bytes >> 24);
		write(u->fd_output, &byte, 1);
		byte = (bytes >> 16);
		write(u->fd_output, &byte, 1);
	}
	byte = (bytes >> 8);
	write(u->fd_output, &byte, 1);
	byte = bytes;
	write(u->fd_output, &byte, 1);
	return (1);
}

int			handle_direct_label(t_asm *u, char *param, t_op_ch *cur_op_ch)
{

	t_inst		*tmp_inst;
	char		*word;

	if (!(word = retrieve_valid_word(param)))
		return (-1);
	if (!(tmp_inst = check_and_retrieve_valid_inst(u, word)))
		return (-1);

	handle_direct_number(u,cur_op_ch, tmp_inst->index - cur_op_ch->index);
	return (1);
}

int		handle_direct_digit(t_asm *u, char *param, t_op_ch *cur_op_ch)
{

	handle_direct_number(u,cur_op_ch, ft_atoi(param));
	return (1);
}

void	handle_direct(t_asm *u, char *param, t_op_ch *cur_op_ch)
{

	
	if(ft_isdigit((*param)) || (*param) ==  '-')
	{
		handle_direct_digit(u, param, cur_op_ch);
	}
	else if ((*param) == LABEL_CHAR)
	{
		handle_direct_label(u, param, cur_op_ch);
	}
	else
	{
		ft_putendl("------------");
		ft_putendl("ERRRRROOORRR");
		ft_putendl(param);
		ft_putendl("------------");
	}

}