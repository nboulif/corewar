/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_handler_basic.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int handle_label_live(t_process *proc) //DONE
{
	// ft_putstr("I'm alive - ");
	// ft_putnbr(proc->champion->id);
	// ft_putendl(" ");

	int dir;
	int index;

	index = 1;
	dir = u_vm->hdl_param[DIR_CODE](proc, &index);

	// mvprintw(50, (64 * 3) + 5, " %d  -  %d", dir, proc->champion->id);
	// move(64, 65);
	// refresh();
	
	u_vm->nbr_live++;
	if (dir < 0 && ((uint32_t)-(dir)) <= u_vm->nb_champion)
	{
		if (dir == proc->champion->id)
			proc->nbr_live++;
		u_vm->champions[-(dir) - 1]->total_lives++;
		u_vm->champions[-(dir) - 1]->last_live = u_vm->cycle_passed;
		
		nc_print_mem(proc->pc, NC_COLOR_WHITE, u_vm->champions[-(dir) - 1]->nc_color);
	}
	
	proc->pc = calc_addr(proc->pc + index);
	return (1);
}

int handle_label_zjmp(t_process *proc) // DONE
{
	int address;
	int index;

	index = 1;
	address = u_vm->hdl_param[DIR_CODE](proc, &index);

	// mvprintw(60 + -(proc->champion->id), (64 * 3) + 5, "zjmp	8 %d %s %d  %d  %d   ", 
	// 	proc->champion->id, proc->cur_op->name, 
	// 	proc->carry, proc->pc, calc_addr(address % IDX_MOD));
	// move(64, 65);
	// refresh();

	if (proc->carry == 1)
	 
		proc->pc = calc_addr(proc->pc + (address % IDX_MOD));
	else
		proc->pc = calc_addr(proc->pc + index);
	return (1);
}


int handle_label_aff(t_process *proc) // DONE
{
	
	ft_putchar(proc->regs[(*(u_vm->mem_data + calc_addr(proc->pc + 1))) - 1]);

	proc->pc = calc_addr(proc->pc + 2);
	
	return (1);
}
