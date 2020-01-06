/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhunders <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 14:00:56 by rhunders          #+#    #+#             */
/*   Updated: 2019/12/20 14:03:38 by rhunders         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

int		read_int_in_map(t_all *all, int pc)
{
	int ret;

	ret = 0;
	move_pc(&pc, 0);
	ret |= ((int)(unsigned char)all->map.character[pc]) << 24;
	move_pc(&pc, 1);
	ret |= ((int)(unsigned char)all->map.character[pc]) << 16;
	move_pc(&pc, 1);
	ret |= ((int)(unsigned char)all->map.character[pc]) << 8;
	move_pc(&pc, 1);
	ret |= (int)(unsigned char)all->map.character[pc];
	return (ret);
}

void	print_error_and_exit(int type_of_error)
{
	static char *str[9] = {"READ ERROR\n", "BAD MAGIC NUMBER\n",
					"INDEX DOUBLON\n", "TOO MUCH CHAMPS\n",
					"MALLOC ERROR\n", "OPEN FAILED\n",
					"INCOMPLETE ARGUMENT\n", "BAD EXEC_SIZE\n",
					"INVALID CYCLE AMOUNT (DUMP)\n"};

	ft_putstr_fd(str[-type_of_error - 1], 2);
	exit(1);
}

void	move_pc(int *pc, int incr)
{
	if (incr >= MEM_SIZE || incr <= -MEM_SIZE)
		incr %= MEM_SIZE;
	*pc = (*pc + incr) % MEM_SIZE;
	if (*pc < 0)
		*pc = MEM_SIZE + *pc;
}
