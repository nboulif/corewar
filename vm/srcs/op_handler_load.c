/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_handler_load.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int handle_label_ld_lld(t_process *proc) // DONE
{
	int index;
	int32_t *reg;
	uint16_t addr;
	int val;
	// int val1;
	uint8_t codage_octal;

	index = 1;
	codage_octal = *(u_vm->mem_data + calc_addr(proc->pc + index++));
	if ( 
	((codage_octal >> 6) & 3) && (u_vm->hdl_conv_code_type[(codage_octal >> 6) & 3]() | proc->cur_op->argv[0])
	&& ((codage_octal >> 4) & 3) && (u_vm->hdl_conv_code_type[(codage_octal >> 4) & 3]() | proc->cur_op->argv[1])
		)
		{
		if (((codage_octal >> 6) & 3) == T_IND)
		{
			addr = 0;
			addr = (addr | *(u_vm->mem_data + calc_addr(proc->pc + index++))) << 8;
			addr = (addr | *(u_vm->mem_data + calc_addr(proc->pc + index++)));
			if (proc->cur_op->op_code == 2)
			{
				val = 0;
				val = (val | *(u_vm->mem_data + calc_addr(proc->pc + ((addr + 0) % IDX_MOD)))) << 8;
				val = (val | *(u_vm->mem_data + calc_addr(proc->pc + ((addr + 1) % IDX_MOD)))) << 8;
				val = (val | *(u_vm->mem_data + calc_addr(proc->pc + ((addr + 2) % IDX_MOD)))) << 8;
				val = (val | *(u_vm->mem_data + calc_addr(proc->pc + ((addr + 3) % IDX_MOD))));
			}
			else
			{
				val = 0;
				val = (val | *(u_vm->mem_data + calc_addr(proc->pc + addr + 0))) << 8;
				val = (val | *(u_vm->mem_data + calc_addr(proc->pc + addr + 1))) << 8;
				val = (val | *(u_vm->mem_data + calc_addr(proc->pc + addr + 2))) << 8;
				val = (val | *(u_vm->mem_data + calc_addr(proc->pc + addr + 3)));
			}
		}
		else
			val = u_vm->hdl_param[(codage_octal >> 6) & 3](proc, &index, 0);

		reg = &proc->regs[(*(u_vm->mem_data + calc_addr(proc->pc + index++))) - 1];

		*(reg) = val;

		proc->pc = calc_addr(proc->pc + index);

		proc->carry = (!(*reg));
	}
	else
	{
		proc->pc = calc_addr(proc->pc + 1);
	}
	return (1);
}


int handle_label_ldi_lldi(t_process *proc) // DONE
{
	int index;	
	int i_1;
	// int i_11;
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
		// mvprintw(45 + -(proc->champion->id), (64 * 3) + 5, "lldi1    %d %d    %d %d %d ",
		// 	proc->champion->id, proc->pc, (codage_octal >> 6) & 3, (codage_octal >> 4) & 3, (codage_octal >> 2) & 3);
		// move(64, 65);
		// refresh();
		i_1 = u_vm->hdl_param[(codage_octal >> 6) & 3](proc, &index);
		i_2 = u_vm->hdl_param[(codage_octal >> 4) & 3](proc, &index);
		reg = &proc->regs[(*(u_vm->mem_data + calc_addr(proc->pc + index++))) - 1];

		// mvprintw(45 + -(proc->champion->id), (64 * 3) + 5, "lldi2    %d %d %d  %d  %d   ",
		// 	proc->champion->id, proc->pc, 
		// 	i_1, i_2, *reg);
		// move(64, 65);
		// refresh();
		// if (reg >= 0 && reg <= 16)
		if (proc->cur_op->op_code == 10)
		{
			(*reg) = 0;
			(*reg) = ((*reg) | *(u_vm->mem_data + calc_addr(proc->pc + ((i_1 + i_2 + 0) % IDX_MOD)))) << 8;
			(*reg) = ((*reg) | *(u_vm->mem_data + calc_addr(proc->pc + ((i_1 + i_2 + 1) % IDX_MOD)))) << 8;
			(*reg) = ((*reg) | *(u_vm->mem_data + calc_addr(proc->pc + ((i_1 + i_2 + 2) % IDX_MOD)))) << 8;
			(*reg) = ((*reg) | *(u_vm->mem_data + calc_addr(proc->pc + ((i_1 + i_2 + 3) % IDX_MOD))));
		}
		else
		{
			(*reg) = 0;
			(*reg) = ((*reg) | *(u_vm->mem_data + calc_addr(proc->pc + i_1 + i_2 + 0))) << 8;
			(*reg) = ((*reg) | *(u_vm->mem_data + calc_addr(proc->pc + i_1 + i_2 + 1))) << 8;
			(*reg) = ((*reg) | *(u_vm->mem_data + calc_addr(proc->pc + i_1 + i_2 + 2))) << 8;
			(*reg) = ((*reg) | *(u_vm->mem_data + calc_addr(proc->pc + i_1 + i_2 + 3)));
			proc->carry = (!(*reg));
		}
		proc->pc = calc_addr(proc->pc + index);
	}
	else
	{
		proc->pc = calc_addr(proc->pc + 1);
	}
	
	
	
	return (1);
}
