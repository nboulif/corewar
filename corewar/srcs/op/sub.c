/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 00:53:34 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/14 00:53:35 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void		op_sub(t_all *all, t_process *p)
{
	if (parse_arg_op(all, p))
	{
		p->reg[p->op.params[2] - 1] =
			p->reg[*p->op.params - 1] - p->reg[p->op.params[1] - 1];
		p->carry = !p->reg[p->op.params[2] - 1];
	}
}
