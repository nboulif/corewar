/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_handler_fork.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int handle_label_forks(t_process *proc) // DONE
{
	t_process 	*last_proc;
	int index;
	int dir;

	index = 1;
	dir = u_vm->hdl_param[DIR_CODE](proc, &index);

	last_proc = proc;
	while (last_proc->next)
		last_proc = last_proc->next;
	
	last_proc->next = (t_process*)malloc(sizeof(t_process));

	int i;
	
	i = -1;
	while (++i < REG_NUMBER)
		last_proc->next->regs[i] = proc->regs[i];
	
	if (proc->cur_op->op_code == 12)
		last_proc->next->pc = calc_addr(proc->pc + (dir % IDX_MOD));
	else
		last_proc->next->pc = calc_addr(proc->pc + (dir));

	last_proc->next->old_pc = last_proc->next->pc;
	
	last_proc->next->carry = proc->carry;

	last_proc->next->cycle_to_run = proc->cycle_to_run + 1;
	last_proc->next->nbr_live = 0;
	last_proc->next->cur_op = NULL;

	last_proc->next->champion = proc->champion;

	last_proc->next->prev = last_proc;
	last_proc->next->next = NULL;
	
	proc->champion->nb_processes++;

	// mvprintw(60 + -(proc->champion->id), (64 * 3) + 5, "test	8 %d %s %d  %d  %d   ", 
	// 	proc->champion->id, proc->cur_op->name, proc->champion->nb_processes, proc->pc, last_proc->next->pc);
	// move(64, 65);
	// refresh();

	proc->pc = calc_addr(proc->pc + index);
	return (1);
}
