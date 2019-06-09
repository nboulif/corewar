/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_handler_store.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int handle_label_st(t_process *proc) // DONE
{
	int index;
	int32_t *reg;
	int32_t val;
	uint8_t codage_octal;

	index = 1;
	codage_octal = *(u_vm->mem_data + calc_addr(proc->pc + index++));

	if ( 
	((codage_octal >> 6) & 3) && (u_vm->hdl_conv_code_type[(codage_octal >> 6) & 3]() | proc->cur_op->argv[0])
	&& ((codage_octal >> 4) & 3) && (u_vm->hdl_conv_code_type[(codage_octal >> 4) & 3]() | proc->cur_op->argv[1])
		)
	{
		reg = &proc->regs[(*(u_vm->mem_data + calc_addr(proc->pc + index++))) - 1];
		
		if (((codage_octal >> 4) & 3) == REG_CODE)
		{
			proc->regs[(*(u_vm->mem_data + calc_addr(proc->pc + index++))) - 1] = (*reg);
		}
		else if (((codage_octal >> 4) & 3) == IND_CODE)
		{
			val = u_vm->hdl_param[(codage_octal >> 4) & 3](proc, &index);

			*(u_vm->mem_data + calc_addr(proc->pc + ((val + 0) % IDX_MOD))) = ((*reg) >> 24) & 255;
			*(u_vm->mem_data + calc_addr(proc->pc + ((val + 1) % IDX_MOD))) = ((*reg) >> 16) & 255;
			*(u_vm->mem_data + calc_addr(proc->pc + ((val + 2) % IDX_MOD))) = ((*reg) >> 8) & 255;
			*(u_vm->mem_data + calc_addr(proc->pc + ((val + 3) % IDX_MOD))) = ((*reg) >> 0) & 255;
			
			u_vm->mem_stat[calc_addr(proc->pc + ((val + 0) % IDX_MOD))]->color = proc->champion->color;
			u_vm->mem_stat[calc_addr(proc->pc + ((val + 1) % IDX_MOD))]->color = proc->champion->color;
			u_vm->mem_stat[calc_addr(proc->pc + ((val + 2) % IDX_MOD))]->color = proc->champion->color;
			u_vm->mem_stat[calc_addr(proc->pc + ((val + 3) % IDX_MOD))]->color = proc->champion->color;

			u_vm->mem_stat[calc_addr(proc->pc + ((val + 0) % IDX_MOD))]->nc_color = proc->champion->nc_color;
			u_vm->mem_stat[calc_addr(proc->pc + ((val + 1) % IDX_MOD))]->nc_color = proc->champion->nc_color;
			u_vm->mem_stat[calc_addr(proc->pc + ((val + 2) % IDX_MOD))]->nc_color = proc->champion->nc_color;
			u_vm->mem_stat[calc_addr(proc->pc + ((val + 3) % IDX_MOD))]->nc_color = proc->champion->nc_color;

			nc_print(calc_addr(proc->pc + ((val + 0) % IDX_MOD)));
			nc_print(calc_addr(proc->pc + ((val + 1) % IDX_MOD)));
			nc_print(calc_addr(proc->pc + ((val + 2) % IDX_MOD)));
			nc_print(calc_addr(proc->pc + ((val + 3) % IDX_MOD)));
		}

		proc->pc = calc_addr(proc->pc + index);
	}
	else
	{
		proc->pc = calc_addr(proc->pc + 1);
	}
	return (1);
}

int handle_label_sti(t_process *proc) // DONE ?
{
	int index;
	// int i_11;
	int i_1;
	int i_2;
	int32_t *reg;
	uint8_t codage_octal;

	index = 1;
	codage_octal = *(u_vm->mem_data + calc_addr(proc->pc + index++));
	if ( 
	((codage_octal >> 6) & 3) && (u_vm->hdl_conv_code_type[(codage_octal >> 6) & 3]() | proc->cur_op->argv[0])
	&& ((codage_octal >> 4) & 3) && (u_vm->hdl_conv_code_type[(codage_octal >> 4) & 3]() | proc->cur_op->argv[1])
	&& ((codage_octal >> 2) & 3) && (u_vm->hdl_conv_code_type[(codage_octal >> 2) & 3]() | proc->cur_op->argv[2])
		)
	{
		reg = &proc->regs[(*(u_vm->mem_data + calc_addr(proc->pc + index++))) - 1];
		i_1 = u_vm->hdl_param[(codage_octal >> 4) & 3](proc, &index);
		i_2 = u_vm->hdl_param[(codage_octal >> 2) & 3](proc, &index);
		// mvprintw(45 + -(proc->champion->id), (64 * 3) + 5, "sti   ch_id %d  pc %d  i1 %d  i2 %d  reg %d %d",
		// 		 proc->champion->id, proc->pc, i_1, i_2, (*(u_vm->mem_data + calc_addr(proc->pc + 2))), *reg);
		// move(64, 65);
		// refresh();

		// mvprintw(50 + -(proc->champion->id), (64 * 3) + 5, "----- i1 %d  i2 %d   addr %d  %d  %d",
		// 		 i_1, i_2, ((i_1 + i_2 + 0) % IDX_MOD),
		// 		 proc->pc + ((i_1 + i_2 + 0) % IDX_MOD),
		// 		 calc_addr(proc->pc + ((i_1 + i_2 + 0) % IDX_MOD)));
		// move(64, 65);
		// refresh();
		*(u_vm->mem_data + calc_addr(proc->pc +((i_1 + i_2 + 0) % IDX_MOD))) = ((*reg) >> 24) & 255;
		*(u_vm->mem_data + calc_addr(proc->pc +((i_1 + i_2 + 1) % IDX_MOD))) = ((*reg) >> 16) & 255;
		*(u_vm->mem_data + calc_addr(proc->pc +((i_1 + i_2 + 2) % IDX_MOD))) = ((*reg) >> 8) & 255;
		*(u_vm->mem_data + calc_addr(proc->pc +((i_1 + i_2 + 3) % IDX_MOD))) = ((*reg) >> 0) & 255;

		u_vm->mem_stat[calc_addr(proc->pc + ((i_1 + i_2 + 0) % IDX_MOD))]->color = proc->champion->color;
		u_vm->mem_stat[calc_addr(proc->pc + ((i_1 + i_2 + 1) % IDX_MOD))]->color = proc->champion->color;
		u_vm->mem_stat[calc_addr(proc->pc + ((i_1 + i_2 + 2) % IDX_MOD))]->color = proc->champion->color;
		u_vm->mem_stat[calc_addr(proc->pc + ((i_1 + i_2 + 3) % IDX_MOD))]->color = proc->champion->color;

		u_vm->mem_stat[calc_addr(proc->pc + ((i_1 + i_2 + 0) % IDX_MOD))]->nc_color = proc->champion->nc_color;
		u_vm->mem_stat[calc_addr(proc->pc + ((i_1 + i_2 + 1) % IDX_MOD))]->nc_color = proc->champion->nc_color;
		u_vm->mem_stat[calc_addr(proc->pc + ((i_1 + i_2 + 2) % IDX_MOD))]->nc_color = proc->champion->nc_color;
		u_vm->mem_stat[calc_addr(proc->pc + ((i_1 + i_2 + 3) % IDX_MOD))]->nc_color = proc->champion->nc_color;

		nc_print(calc_addr(proc->pc + ((i_1 + i_2 + 0) % IDX_MOD)));
		nc_print(calc_addr(proc->pc + ((i_1 + i_2 + 1) % IDX_MOD)));
		nc_print(calc_addr(proc->pc + ((i_1 + i_2 + 2) % IDX_MOD)));
		nc_print(calc_addr(proc->pc + ((i_1 + i_2 + 3) % IDX_MOD)));

		proc->pc = calc_addr(proc->pc + index);
	}
	else
	{
		proc->pc = calc_addr(proc->pc + 1);
	}
	return (1);
}