/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		handle_register(t_asm *u, char *param)
{

	int byte;

	byte = ft_atoi(param);
	write(u->fd_output, &byte, 1);

	ft_putstr("reg ");
	ft_putnbr(byte);
	ft_putstr("  ");

	return (1);
}

int		handle_number(t_asm *u, char *param)
{
	unsigned int	bytes;
	unsigned int	byte;
	int				nb;
	
	nb = ft_atoi(param);

	if (nb >= 0)
		bytes = nb;
	else
		bytes = (INT_MAX + nb) + 1;
		
	byte = (bytes >> 8);
	write(u->fd_output, &byte, 1);
	byte = bytes;
	write(u->fd_output, &byte, 1);

	ft_putnbr(byte);
	ft_putstr("  ");
	return (1);
}


int		handle_extend(t_asm *u)
{
	t_inst 		*last_inst;
	t_op_ch		*last_op;

	last_inst = u->prog->insts;
	while (last_inst->next)
		last_inst = last_inst->next;

	ft_strdel(&u->prog->insts->name);

	if (!(u->prog->insts->name = ft_strdup(last_inst->name)))
	{
		ft_putendl("------------");
		ft_putendl("error 429");
		ft_putendl("------------");
		return (0);
	}
	
	last_op = last_inst->ops;

	if (last_op)
	{
		while (last_op->next)
			last_op = last_op->next;
		last_op->next = u->prog->insts->ops;
		u->prog->insts->ops->prev = last_op->next;
	}
	else
	{
		last_op = u->prog->insts->ops;
	}
	
	return (1);
}
