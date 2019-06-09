/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_handler_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

uint32_t		calc_addr(int addr)
{
	addr %= MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	return (addr);
}


uint8_t retr_reg_type(void)
{
	return(T_REG);
}
uint8_t retr_dir_type(void)
{
	return(T_DIR);
}
uint8_t retr_ind_type(void)
{
	return(T_IND);
}

int32_t read_param_reg(t_process *proc, int *index)
{
	return (proc->regs[*(u_vm->mem_data + calc_addr(proc->pc + (*index)++)) - 1]);
}

int32_t read_param_ind(t_process *proc, int *index)
{
	uint16_t		addr;
	int32_t 		val;
	// mvprintw(47 + -(proc->champion->id), (64 * 3) + 5, "-I2---   ch_id");
	// move(64, 65);
	// refresh();
	addr = 0;
	addr = (addr | *(u_vm->mem_data + calc_addr(proc->pc + (*index)++))) << 8;
	addr = (addr | *(u_vm->mem_data + calc_addr(proc->pc + (*index)++)));

	val = 0;
	val = (val | *(u_vm->mem_data + calc_addr(proc->pc + ((addr + 0) % IDX_MOD)))) << 8;
	val = (val | *(u_vm->mem_data + calc_addr(proc->pc + ((addr + 1) % IDX_MOD)))) << 8;
	val = (val | *(u_vm->mem_data + calc_addr(proc->pc + ((addr + 2) % IDX_MOD)))) << 8;
	val = (val | *(u_vm->mem_data + calc_addr(proc->pc + ((addr + 3) % IDX_MOD))));

	return (val);
}

int32_t read_param_dir(t_process *proc, int *index)
{
	int16_t			argv_2;
	int32_t			argv_4;

	if (proc->cur_op->dir_size)
	{
		argv_2 = 0;
		argv_2 = (argv_2 | *(u_vm->mem_data + calc_addr(proc->pc + (*index)++))) << 8;
		argv_2 = (argv_2 | *(u_vm->mem_data + calc_addr(proc->pc + (*index)++)));
		return (argv_2);
	}
	else
	{
		argv_4 = 0;
		argv_4 = (argv_4 | *(u_vm->mem_data + calc_addr(proc->pc + (*index)++))) << 8;
		argv_4 = (argv_4 | *(u_vm->mem_data + calc_addr(proc->pc + (*index)++))) << 8;
		argv_4 = (argv_4 | *(u_vm->mem_data + calc_addr(proc->pc + (*index)++))) << 8;
		argv_4 = (argv_4 | *(u_vm->mem_data + calc_addr(proc->pc + (*index)++)));
		return (argv_4);
	}
}


void			init_handlers(void)
{
	u_vm->hdl_param[REG_CODE] = &read_param_reg;
	u_vm->hdl_param[DIR_CODE] = &read_param_dir;
	u_vm->hdl_param[IND_CODE] = &read_param_ind;

	u_vm->hdl_conv_code_type[REG_CODE] = &retr_reg_type;
	u_vm->hdl_conv_code_type[DIR_CODE] = &retr_dir_type;
	u_vm->hdl_conv_code_type[IND_CODE] = &retr_ind_type;

	u_vm->handlers[0] = &handle_label_live;
	u_vm->handlers[1] = &handle_label_ld_lld;
	u_vm->handlers[2] = &handle_label_st;
	u_vm->handlers[3] = &handle_label_add_sub;
	u_vm->handlers[4] = &handle_label_add_sub;
	u_vm->handlers[5] = &handle_label_and_or_xor;
	u_vm->handlers[6] = &handle_label_and_or_xor;
	u_vm->handlers[7] = &handle_label_and_or_xor;
	u_vm->handlers[8] = &handle_label_zjmp;
	u_vm->handlers[9] = &handle_label_ldi_lldi;
	u_vm->handlers[10] = &handle_label_sti;
	u_vm->handlers[11] = &handle_label_forks;
	u_vm->handlers[12] = &handle_label_ld_lld;
	u_vm->handlers[13] = &handle_label_ldi_lldi;
	u_vm->handlers[14] = &handle_label_forks;
	u_vm->handlers[15] = &handle_label_aff;
}
