/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:52:32 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/14 00:52:35 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		op_aff(t_all *all, t_process *proc)
{
	if (parse_arg_op(all, proc) && !(all->flag & FLAG_VISU) &&
		!(all->flag & FLAG_RESUME))
		ft_printf("Aff: %c\n", (unsigned char)proc->reg[proc->op.params[0] - 1] % 256);
}
