/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_1.c                                        :+:      :+:    :+:   */
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

	tmp_inst = u->insts;

	while (tmp_inst && ft_strcmp(tmp_inst->name, word))
			tmp_inst = tmp_inst->next;
		
	if (!tmp_inst)
	{
		ft_putendl("ERROR 873");
		return (NULL);
	}
	return (tmp_inst);
}

int			handle_direct_number(t_asm *u, t_op_ch *cur_op_ch, int nb, int from_255)
{

	unsigned int	bytes;
	unsigned int	byte;

	(void)from_255;

	if (nb >= 0)
		bytes = (unsigned int)nb;
	else
		bytes = (unsigned int)((INT_MAX + nb) + 1);
	if (!cur_op_ch->op->dir_size)
	{
		ft_putstr("------------- ");
		ft_putnbr(bytes);
		ft_putendl("-------------44");
		byte = (bytes >> 24);
		ft_putstr("------------- ");
		ft_putnbr(byte);
		ft_putendl("-------------44");
		write(u->fd_output, &byte, 1);
		byte = (bytes >> 16);
		write(u->fd_output, &byte, 1);

		// byte = (bytes >> 16);
		// write(u->fd_output, &byte, -2);
	}

	byte = (bytes >> 8);
	write(u->fd_output, &byte, 1);
	byte = bytes;
	write(u->fd_output, &byte, 1);
	// byte = bytes;
	// write(u->fd_output, &byte, 2);
	// int			byte;

	// if (!from_255)
	// 	byte = 0;
	// else
	// 	byte = 255;

	// if (!cur_op_ch->op->dir_size)
	// {
	// 	write(u->fd_output, &byte, 1);
	// 	write(u->fd_output, &byte, 1);
	// }

	// if (nb < 0)
	// 	nb = -nb - 1;

	// if (nb > 255)
	// 	byte -= nb / 255;
	// else
	// 	byte += nb / 255;

	// write(u->fd_output, &byte, 1);
	// byte = nb % 255;

	// if (!from_255)
	// 	byte = nb;
	// else
	// 	byte = 255 - nb;
	
	// write(u->fd_output, &byte, 1);



	// ft_putnbr(byte);
	// ft_putstr("  ");
	return (1);
}

int			handle_direct_label(t_asm *u, char *param, t_op_ch *cur_op_ch)
{

	t_inst		*tmp_inst;
	char		*word;
	// int			tmp_byte;
	// int			byte;

	if (!(word = retrieve_valid_word(param)))
		return (-1);
	if (!(tmp_inst = check_and_retrieve_valid_inst(u, word)))
		return (-1);
	
	// ft_putnbr(cur_inst->index);
	// ft_putstr("  ");
	// ft_putnbr(cur_op_ch->index);
	// ft_putendl(" ");

	
	handle_direct_number(u,cur_op_ch,
		tmp_inst->index - cur_op_ch->index, 
		tmp_inst->index > cur_op_ch->index ? 0 : 1);

	// tmp_byte = tmp_inst->index - cur_op_ch->index;

	// if (tmp_inst->index > cur_op_ch->index)
	// 	byte = 0;
	// else
	// 	byte = 255;

	// if (!cur_op_ch->op->dir_size)
	// {
	// 	write(u->fd_output, &byte, 1);
	// 	write(u->fd_output, &byte, 1);
	// }

	// if (tmp_byte < 0)
	// 	tmp_byte = -tmp_byte - 1;

	// if (tmp_byte > 255)
	// 	byte -= tmp_byte / 255;
	// else
	// 	byte += tmp_byte / 255;
	// write(u->fd_output, &byte, 1);

	// byte = tmp_byte % 255;
	// if (tmp_inst->index > cur_op_ch->index)
	// 	byte = tmp_byte;
	// else
	// 	byte = 255 - tmp_byte;
	// write(u->fd_output, &byte, 1);

	// 		ft_putnbr(tmp_byte);
	// 		ft_putstr("  ");
	// 		ft_putnbr(byte);
	// 		ft_putstr("  ");
	return (1);
}

int		handle_direct_digit(t_asm *u, char *param, t_op_ch *cur_op_ch)
{

	// int			tmp_byte;
	// int			byte;



	handle_direct_number(u,cur_op_ch, 
		ft_atoi(param), 
		ft_atoi(param) < 0 ? 1 : 0);

	// tmp_byte = ft_atoi(param);

	// if (tmp_byte < 0)
	// 	byte = 255;
	// else
	// 	byte = 0;

	// if (!cur_op_ch->op->dir_size)
	// {
	// 	write(u->fd_output, &byte, 1);
	// 	write(u->fd_output, &byte, 1);
	// }

	// write(u->fd_output, &byte, 1);
	
	// byte = tmp_byte;
	
	// if (tmp_byte < 0)
	// 	byte = 255 + byte + 1;
	
	// write(u->fd_output, &byte, 1);

	// ft_putnbr(byte);
	// ft_putstr("  ");
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