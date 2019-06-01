/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_2.c                                        :+:      :+:    :+:   */
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
