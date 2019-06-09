/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_handler_arithm_binary.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int handle_label_add_sub(t_process *proc) // DONE
{
	int index;
	int r_1;
	int r_2;
	int32_t *r_res;
	uint8_t codage_octal;

	index = 1;
	codage_octal = *(u_vm->mem_data + calc_addr(proc->pc + index++));
	if ( 
	((codage_octal >> 6) & 3) && (u_vm->hdl_conv_code_type[(codage_octal >> 6) & 3]() | proc->cur_op->argv[0])
	&& ((codage_octal >> 4) & 3) && (u_vm->hdl_conv_code_type[(codage_octal >> 4) & 3]() | proc->cur_op->argv[1])
	&& ((codage_octal >> 2) & 3) && (u_vm->hdl_conv_code_type[(codage_octal >> 2) & 3]() | proc->cur_op->argv[2])
		)
	{
		r_1 = proc->regs[(*(u_vm->mem_data + calc_addr(proc->pc + index++))) - 1];
		r_2 = proc->regs[(*(u_vm->mem_data + calc_addr(proc->pc + index++))) - 1];
		r_res = &proc->regs[(*(u_vm->mem_data + calc_addr(proc->pc + index++))) - 1];

		if (proc->cur_op->op_code == 4)
			(*r_res) = r_1 + r_2;
		else if (proc->cur_op->op_code == 5)
			(*r_res) = r_1 - r_2;
		proc->pc = calc_addr(proc->pc + index);
		
		proc->carry = (!(*r_res));
	}
	else
	{
		proc->pc = calc_addr(proc->pc + 1);
	}
	return (1);
}

int handle_label_and_or_xor(t_process *proc) // DONE
{
	int index;
	int v_1;
	int v_2;
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
		v_1 = u_vm->hdl_param[(codage_octal >> 6) & 3](proc, &index);
		v_2 = u_vm->hdl_param[(codage_octal >> 4) & 3](proc, &index);
		reg = &proc->regs[(*(u_vm->mem_data + calc_addr(proc->pc + index++))) - 1];
		
		if (proc->cur_op->op_code == 6)
			(*reg) = v_1 & v_2;
		else if (proc->cur_op->op_code == 7)
			(*reg) = v_1 | v_2;
		else if (proc->cur_op->op_code == 8)
			(*reg) = v_1 ^ v_2;

		proc->pc = calc_addr(proc->pc + index);
		
		proc->carry = (!(*reg));
	}
	else
	{
		proc->pc = calc_addr(proc->pc + 1);
	}
	return (1);
}
