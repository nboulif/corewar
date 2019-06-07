/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		calc_addr(int addr)
{
	addr %= MEM_SIZE;
	if (addr < 0)
		addr += MEM_SIZE;
	return (addr);
}

int read_param(t_process *proc, unsigned int param_code, int *index)
{
	int argv;

	argv = 0;
	if (param_code == REG_CODE)
	{
		argv = u_vm->memory[proc->pc + (*index)++]->data;
	}
	else if (param_code == DIR_CODE)
	{
		if (!proc->cur_op->dir_size)
		{
			argv =  (argv | u_vm->memory[proc->pc + (*index)++]->data) << 8;
			argv =  (argv | u_vm->memory[proc->pc + (*index)++]->data) << 8;
			argv =  (argv | u_vm->memory[proc->pc + (*index)++]->data) << 8;
			argv =  (argv | u_vm->memory[proc->pc + (*index)++]->data);
		}
		else
		{
			argv |= u_vm->memory[proc->pc + (*index)++]->data << 8;
			argv |= u_vm->memory[proc->pc + (*index)++]->data;
			argv = (short)argv;
		}
	}
	else if (param_code == IND_CODE)
	{
		argv |= u_vm->memory[proc->pc + (*index)++]->data << 8;
		argv |= u_vm->memory[proc->pc + (*index)++]->data;
		argv = (short)argv;
	}
	return (argv);
}

int handle_label_live(t_process *proc) //DONE
{
	// ft_putstr("I'm alive - ");
	// ft_putnbr(proc->champion->id);
	// ft_putendl(" ");

	unsigned int dir;
	int index;

	index = 1;
	dir = read_param(proc, DIR_CODE, &index);
	
	u_vm->nbr_live++;
	if (dir && dir <= u_vm->nb_champion)
	{
		if (dir == proc->champion->id)
			proc->nbr_live++;
		u_vm->champions[dir - 1]->total_lives++;
		u_vm->champions[dir - 1]->last_live = u_vm->cycle_passed;
	}	
	
	proc->pc += index;
	return (1);
}

int handle_label_ld(t_process *proc) // DONE
{
	int index;
	int reg;
	int val;
	int val1;
	int codage_octal;

	index = 1;
	codage_octal = u_vm->memory[proc->pc + index++]->data;
	val = read_param(proc, ((codage_octal >> 6) & 3), &index);
	reg = read_param(proc, ((codage_octal >> 4) & 3), &index);

	if (((codage_octal >> 6) & 3) == IND_CODE)
	{
		val1 = val;
		val = 0;
		val = (val | u_vm->memory[(proc->pc + (val1 % IDX_MOD) + 0) % MEM_SIZE]->data) << 8;
		val = (val | u_vm->memory[(proc->pc + (val1 % IDX_MOD) + 1) % MEM_SIZE]->data) << 8;
		val = (val | u_vm->memory[(proc->pc + (val1 % IDX_MOD) + 2) % MEM_SIZE]->data) << 8;
		val = (val | u_vm->memory[(proc->pc + (val1 % IDX_MOD) + 3) % MEM_SIZE]->data);

	}

	proc->regs[reg - 1] = val;

	proc->pc += index;

	proc->carry = 1;
	return (1);
}

int handle_label_st(t_process *proc) // DONE
{
	int index;
	int reg;
	int val;
	int codage_octal;

	index = 1;
	codage_octal = u_vm->memory[proc->pc + index++]->data;
	reg = read_param(proc, ((codage_octal >> 6) & 3), &index);
	val = read_param(proc, ((codage_octal >> 4) & 3), &index);
	
	if (((codage_octal >> 4) & 3) == IND_CODE)
	{	
		u_vm->memory[(proc->pc + (val % IDX_MOD) + 0) % MEM_SIZE]->data = (proc->regs[reg - 1] >> 24) & 255;	
		u_vm->memory[(proc->pc + (val % IDX_MOD) + 0) % MEM_SIZE]->color = proc->champion->color;	
		u_vm->memory[(proc->pc + (val % IDX_MOD) + 0) % MEM_SIZE]->nc_color = proc->champion->nc_color;	
		nc_print((proc->pc + (val % IDX_MOD) + 0) % MEM_SIZE);
		u_vm->memory[(proc->pc + (val % IDX_MOD) + 1) % MEM_SIZE]->data = (proc->regs[reg - 1] >> 16) & 255;	
		u_vm->memory[(proc->pc + (val % IDX_MOD) + 1) % MEM_SIZE]->color = proc->champion->color;	
		u_vm->memory[(proc->pc + (val % IDX_MOD) + 1) % MEM_SIZE]->nc_color = proc->champion->nc_color;	
		nc_print((proc->pc + (val % IDX_MOD) + 1) % MEM_SIZE);
		u_vm->memory[(proc->pc + (val % IDX_MOD) + 2) % MEM_SIZE]->data = (proc->regs[reg - 1] >> 8) & 255;	
		u_vm->memory[(proc->pc + (val % IDX_MOD) + 2) % MEM_SIZE]->color = proc->champion->color;	
		u_vm->memory[(proc->pc + (val % IDX_MOD) + 2) % MEM_SIZE]->nc_color = proc->champion->nc_color;	
		nc_print((proc->pc + (val % IDX_MOD) + 2) % MEM_SIZE);
		u_vm->memory[(proc->pc + (val % IDX_MOD) + 3) % MEM_SIZE]->data = (proc->regs[reg - 1] >> 0) & 255;	
		u_vm->memory[(proc->pc + (val % IDX_MOD) + 3) % MEM_SIZE]->color = proc->champion->color;	
		u_vm->memory[(proc->pc + (val % IDX_MOD) + 3) % MEM_SIZE]->nc_color = proc->champion->nc_color;	
		nc_print((proc->pc + (val % IDX_MOD) + 3) % MEM_SIZE);
	}
	else if (((codage_octal >> 4) & 3) == REG_CODE)
	{
		proc->regs[val - 1] = proc->regs[reg - 1];	
	}

	proc->pc += index;
	
	return (1);
}

int handle_label_add(t_process *proc) // DONE
{
	int index;
	int r_1;
	int r_2;
	int r_res;
	int codage_octal;

	index = 1;
	codage_octal = u_vm->memory[proc->pc + index++]->data;
	r_1 = read_param(proc, ((codage_octal >> 6) & 3), &index);
	r_2 = read_param(proc, ((codage_octal >> 4) & 3), &index);
	r_res = read_param(proc, ((codage_octal >> 2) & 3), &index);
	
	proc->regs[r_res - 1] = proc->regs[r_1 - 1] + proc->regs[r_2 - 1];

	proc->pc += index;
	
	proc->carry = 1;
	return (1);
}

int handle_label_sub(t_process *proc) // DONE
{
	int index;
	int r_1;
	int r_2;
	int r_res;
	int codage_octal;

	index = 1;
	codage_octal = u_vm->memory[proc->pc + index++]->data;
	r_1 = read_param(proc, ((codage_octal >> 6) & 3), &index);
	r_2 = read_param(proc, ((codage_octal >> 4) & 3), &index);
	r_res = read_param(proc, ((codage_octal >> 2) & 3), &index);
	
	proc->regs[r_res - 1] = proc->regs[r_1 - 1] - proc->regs[r_2 - 1];

	proc->pc += index;
	
	proc->carry = 1;
	return (1);
}

int handle_label_and(t_process *proc) // DONE
{
	int index;
	int v_1;
	int v_11;
	int v_2;
	int v_22;
	int reg;
	int codage_octal;

	index = 1;
	codage_octal = u_vm->memory[proc->pc + index++]->data;
	v_1 = read_param(proc, ((codage_octal >> 6) & 3), &index);
	v_2 = read_param(proc, ((codage_octal >> 4) & 3), &index);
	reg = read_param(proc, ((codage_octal >> 2) & 3), &index);
	if (((codage_octal >> 6) & 3) == IND_CODE)
	{
		v_11 = v_1;
		v_1 = 0;
		v_1 = (v_1 | u_vm->memory[(proc->pc + ((v_11) % IDX_MOD) + 0) % MEM_SIZE]->data) << 8;
		v_1 = (v_1 | u_vm->memory[(proc->pc + ((v_11) % IDX_MOD) + 1) % MEM_SIZE]->data) << 8;
		v_1 = (v_1 | u_vm->memory[(proc->pc + ((v_11) % IDX_MOD) + 2) % MEM_SIZE]->data) << 8;
		v_1 = (v_1 | u_vm->memory[(proc->pc + ((v_11) % IDX_MOD) + 3) % MEM_SIZE]->data);
	}
	else if (((codage_octal >> 6) & 3) == REG_CODE)
		v_1 = proc->regs[v_1 - 1];

	if (((codage_octal >> 4) & 3) == IND_CODE)
	{
		v_22 = v_2;
		v_2 = 0;
		v_2 = (v_2 | u_vm->memory[(proc->pc + ((v_22) % IDX_MOD) + 0) % MEM_SIZE]->data) << 8;
		v_2 = (v_2 | u_vm->memory[(proc->pc + ((v_22) % IDX_MOD) + 1) % MEM_SIZE]->data) << 8;
		v_2 = (v_2 | u_vm->memory[(proc->pc + ((v_22) % IDX_MOD) + 2) % MEM_SIZE]->data) << 8;
		v_2 = (v_2 | u_vm->memory[(proc->pc + ((v_22) % IDX_MOD) + 3) % MEM_SIZE]->data);
	}
	else if (((codage_octal >> 4) & 3) == REG_CODE)
		v_2 = proc->regs[v_2 - 1];

	proc->regs[reg - 1] = v_1 & v_2;

	proc->pc += index;
	
	proc->carry = 1;
	return (1);
}

int handle_label_or(t_process *proc) // DONE
{
	int index;
	int v_1;
	int v_11;
	int v_2;
	int v_22;
	int reg;
	int codage_octal;

	index = 1;
	codage_octal = u_vm->memory[proc->pc + index++]->data;
	v_1 = read_param(proc, ((codage_octal >> 6) & 3), &index);
	v_2 = read_param(proc, ((codage_octal >> 4) & 3), &index);
	reg = read_param(proc, ((codage_octal >> 2) & 3), &index);
	if (((codage_octal >> 6) & 3) == IND_CODE)
	{
		v_11 = v_1;
		v_1 = 0;
		v_1 = (v_1 | u_vm->memory[(proc->pc + ((v_11) % IDX_MOD) + 0) % MEM_SIZE]->data) << 8;
		v_1 = (v_1 | u_vm->memory[(proc->pc + ((v_11) % IDX_MOD) + 1) % MEM_SIZE]->data) << 8;
		v_1 = (v_1 | u_vm->memory[(proc->pc + ((v_11) % IDX_MOD) + 2) % MEM_SIZE]->data) << 8;
		v_1 = (v_1 | u_vm->memory[(proc->pc + ((v_11) % IDX_MOD) + 3) % MEM_SIZE]->data);
	}
	else if (((codage_octal >> 6) & 3) == REG_CODE)
		v_1 = proc->regs[v_1 - 1];

	if (((codage_octal >> 4) & 3) == IND_CODE)
	{
		v_22 = v_2;
		v_2 = 0;
		v_2 = (v_2 | u_vm->memory[(proc->pc + ((v_22) % IDX_MOD) + 0) % MEM_SIZE]->data) << 8;
		v_2 = (v_2 | u_vm->memory[(proc->pc + ((v_22) % IDX_MOD) + 1) % MEM_SIZE]->data) << 8;
		v_2 = (v_2 | u_vm->memory[(proc->pc + ((v_22) % IDX_MOD) + 2) % MEM_SIZE]->data) << 8;
		v_2 = (v_2 | u_vm->memory[(proc->pc + ((v_22) % IDX_MOD) + 3) % MEM_SIZE]->data);
	}
	else if (((codage_octal >> 4) & 3) == REG_CODE)
		v_2 = proc->regs[v_2 - 1];

	proc->regs[reg - 1] = v_1 | v_2;

	proc->pc += index;
	
	proc->carry = 1;
	return (1);
}

int handle_label_xor(t_process *proc) // DONE
{
	int index;
	int v_1;
	int v_11;
	int v_2;
	int v_22;
	int reg;
	int codage_octal;

	index = 1;
	codage_octal = u_vm->memory[proc->pc + index++]->data;
	v_1 = read_param(proc, ((codage_octal >> 6) & 3), &index);
	v_2 = read_param(proc, ((codage_octal >> 4) & 3), &index);
	reg = read_param(proc, ((codage_octal >> 2) & 3), &index);
	if (((codage_octal >> 6) & 3) == IND_CODE)
	{
		v_11 = v_1;
		v_1 = 0;
		v_1 = (v_1 | u_vm->memory[(proc->pc + ((v_11) % IDX_MOD) + 0) % MEM_SIZE]->data) << 8;
		v_1 = (v_1 | u_vm->memory[(proc->pc + ((v_11) % IDX_MOD) + 1) % MEM_SIZE]->data) << 8;
		v_1 = (v_1 | u_vm->memory[(proc->pc + ((v_11) % IDX_MOD) + 2) % MEM_SIZE]->data) << 8;
		v_1 = (v_1 | u_vm->memory[(proc->pc + ((v_11) % IDX_MOD) + 3) % MEM_SIZE]->data);
	}
	else if (((codage_octal >> 6) & 3) == REG_CODE)
		v_1 = proc->regs[v_1 - 1];

	if (((codage_octal >> 4) & 3) == IND_CODE)
	{
		v_22 = v_2;
		v_2 = 0;
		v_2 = (v_2 | u_vm->memory[(proc->pc + ((v_22) % IDX_MOD) + 0) % MEM_SIZE]->data) << 8;
		v_2 = (v_2 | u_vm->memory[(proc->pc + ((v_22) % IDX_MOD) + 1) % MEM_SIZE]->data) << 8;
		v_2 = (v_2 | u_vm->memory[(proc->pc + ((v_22) % IDX_MOD) + 2) % MEM_SIZE]->data) << 8;
		v_2 = (v_2 | u_vm->memory[(proc->pc + ((v_22) % IDX_MOD) + 3) % MEM_SIZE]->data);
	}
	else if (((codage_octal >> 4) & 3) == REG_CODE)
		v_2 = proc->regs[v_2 - 1];

	proc->regs[reg - 1] = v_1 ^ v_2;

	proc->pc += index;
	
	proc->carry = 1;
	return (1);
}

int handle_label_zjmp(t_process *proc) // DONE
{
	int address;
	int index;

	index = 1;
	address = read_param(proc, DIR_CODE, &index);

	// mvprintw(60 + proc->champion->id, (64 * 3) + 5, "test	8 %d %s %d  %d  %d   ", 
	// 	proc->champion->id, proc->cur_op->name, proc->carry, proc->pc, (address % IDX_MOD) % MEM_SIZE);
	// move(64, 65);
	// refresh();

	if (proc->carry == 1)
	{
		proc->pc += (address % IDX_MOD) % MEM_SIZE;
	}
	return (1);
}

int handle_label_ldi(t_process *proc) // DONE
{
	int index;	
	int i_1;
	int i_11;
	int i_2;
	int reg;
	int codage_octal;

	index = 1;
	codage_octal = u_vm->memory[proc->pc + index++]->data;
	i_1 = read_param(proc, ((codage_octal >> 6) & 3), &index);
	i_2 = read_param(proc, ((codage_octal >> 4) & 3), &index);
	reg = read_param(proc, ((codage_octal >> 2) & 3), &index);
	
			
	if (((codage_octal >> 4) & 3) == IND_CODE)
	{
		i_11 = i_1;
		i_1 = 0;
		i_1 = (i_1 | u_vm->memory[(proc->pc + ((i_11) % IDX_MOD) + 0) % MEM_SIZE]->data) << 8;
		i_1 = (i_1 | u_vm->memory[(proc->pc + ((i_11) % IDX_MOD) + 1) % MEM_SIZE]->data) << 8;
		i_1 = (i_1 | u_vm->memory[(proc->pc + ((i_11) % IDX_MOD) + 2) % MEM_SIZE]->data) << 8;
		i_1 = (i_1 | u_vm->memory[(proc->pc + ((i_11) % IDX_MOD) + 3) % MEM_SIZE]->data);
	}
	else if (((codage_octal >> 4) & 3) == REG_CODE)
		i_1 = proc->regs[i_1 - 1];

	if (((codage_octal >> 4) & 3) == REG_CODE)
		i_2 = proc->regs[i_2 - 1];

	proc->regs[reg - 1] = 0;
	proc->regs[reg - 1] = (proc->regs[reg - 1] | u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 0) % MEM_SIZE]->data) << 8;
	proc->regs[reg - 1] = (proc->regs[reg - 1] | u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 1) % MEM_SIZE]->data) << 8;
	proc->regs[reg - 1] = (proc->regs[reg - 1] | u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 2) % MEM_SIZE]->data) << 8;
	proc->regs[reg - 1] = (proc->regs[reg - 1] | u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 3) % MEM_SIZE]->data);

	proc->pc += index;
	
	proc->carry = 1;
	return (1);
}

int handle_label_sti(t_process *proc) // DONE ?
{
	int index;
	int i_11;
	int i_1;
	int i_2;
	int reg;
	int codage_octal;

	index = 1;
	codage_octal = u_vm->memory[proc->pc + index++]->data;
	reg = read_param(proc, ((codage_octal >> 6) & 3), &index);
	i_1 = read_param(proc, ((codage_octal >> 4) & 3), &index);
	i_2 = read_param(proc, ((codage_octal >> 2) & 3), &index);
			

	if (((codage_octal >> 4) & 3) == IND_CODE)
	{
	
	
		i_11 = i_1;
		i_1 = 0;
		i_1 = (i_1 | u_vm->memory[(proc->pc + ((i_11) % IDX_MOD) + 0) % MEM_SIZE]->data) << 8;
		i_1 = (i_1 | u_vm->memory[(proc->pc + ((i_11) % IDX_MOD) + 1) % MEM_SIZE]->data) << 8;
		i_1 = (i_1 | u_vm->memory[(proc->pc + ((i_11) % IDX_MOD) + 2) % MEM_SIZE]->data) << 8;
		i_1 = (i_1 | u_vm->memory[(proc->pc + ((i_11) % IDX_MOD) + 3) % MEM_SIZE]->data);
	}
	else if (((codage_octal >> 4) & 3) == REG_CODE)
		i_1 = proc->regs[i_1 - 1];

	if (((codage_octal >> 4) & 3) == REG_CODE)
		i_2 = proc->regs[i_2 - 1];

	u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 0) % MEM_SIZE]->data = (proc->regs[reg - 1] >> 24) & 255;	
	u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 0) % MEM_SIZE]->color = proc->champion->color;	
	u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 0) % MEM_SIZE]->nc_color = proc->champion->nc_color;	
	nc_print((proc->pc + ((i_1 + i_2) % IDX_MOD) + 0) % MEM_SIZE);
	u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 1) % MEM_SIZE]->data = (proc->regs[reg - 1] >> 16) & 255;	
	u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 1) % MEM_SIZE]->color = proc->champion->color;	
	u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 1) % MEM_SIZE]->nc_color = proc->champion->nc_color;	
	nc_print((proc->pc + ((i_1 + i_2) % IDX_MOD) + 1) % MEM_SIZE);
	u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 2) % MEM_SIZE]->data = (proc->regs[reg - 1] >> 8) & 255;	
	u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 2) % MEM_SIZE]->color = proc->champion->color;	
	u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 2) % MEM_SIZE]->nc_color = proc->champion->nc_color;	
	nc_print((proc->pc + ((i_1 + i_2) % IDX_MOD) + 2) % MEM_SIZE);
	u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 3) % MEM_SIZE]->data = (proc->regs[reg - 1] >> 0) & 255;	
	u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 3) % MEM_SIZE]->color = proc->champion->color;	
	u_vm->memory[(proc->pc + ((i_1 + i_2) % IDX_MOD) + 3) % MEM_SIZE]->nc_color = proc->champion->nc_color;	
	nc_print((proc->pc + ((i_1 + i_2) % IDX_MOD) + 3) % MEM_SIZE);
	
	// print_memory();

	proc->pc += index;
	
	return (1);
}

int handle_label_fork(t_process *proc) // DONE
{
	t_process 	*last_proc;
	int index;
	int dir;

	index = 1;
	dir = read_param(proc, DIR_CODE, &index);

	last_proc = proc;
	while (last_proc->next)
		last_proc = last_proc->next;
	
	last_proc->next = (t_process*)malloc(sizeof(t_process));

	int i;
	
	i = -1;
	while (++i < REG_NUMBER)
		last_proc->next->regs[i] = proc->regs[i];
	
	
	last_proc->next->pc = (proc->pc + (dir % IDX_MOD)) % MEM_SIZE;
	last_proc->next->old_pc = last_proc->next->pc;
	last_proc->next->carry = proc->carry;

	last_proc->next->cycle_to_run = proc->cycle_to_run + 1;
	last_proc->next->nbr_live = 0;
	last_proc->next->cur_op = NULL;

	last_proc->next->champion = proc->champion;

	last_proc->next->prev = last_proc;
	last_proc->next->next = NULL;
	
	proc->champion->nb_processes++;

	mvprintw(60 + proc->champion->id, (64 * 3) + 5, "test	8 %d %s %d  %d  %d   ", 
		proc->champion->id, proc->cur_op->name, proc->champion->nb_processes, proc->pc, last_proc->next->pc);
	move(64, 65);
	refresh();

	proc->pc += index;
	return (1);
}

int handle_label_lld(t_process *proc) // DONE
{
	int index;
	int reg;
	int val;
	int val1;
	int codage_octal;

	index = 1;
	codage_octal = u_vm->memory[proc->pc + index++]->data;
	val = read_param(proc, ((codage_octal >> 6) & 3), &index);
	reg = read_param(proc, ((codage_octal >> 4) & 3), &index);

	if (((codage_octal >> 6) & 3) == IND_CODE)
	{
		val1 = val;
		val = 0;
		val = (val | u_vm->memory[(proc->pc + ((val1)) + 0) % MEM_SIZE]->data) << 8;
		val = (val | u_vm->memory[(proc->pc + ((val1)) + 1) % MEM_SIZE]->data) << 8;
		val = (val | u_vm->memory[(proc->pc + ((val1)) + 2) % MEM_SIZE]->data) << 8;
		val = (val | u_vm->memory[(proc->pc + ((val1)) + 3) % MEM_SIZE]->data);
	}

	proc->regs[reg - 1] = val;

	proc->pc += index;

	proc->carry = 1;
	return (1);
}

int handle_label_lldi(t_process *proc) // DONE
{
	int index;	
	int i_1;
	int i_11;
	int i_2;
	int reg;
	int codage_octal;
	
	index = 1;
	codage_octal = u_vm->memory[proc->pc + index++]->data;
	i_1 = read_param(proc, ((codage_octal >> 6) & 3), &index);
	i_2 = read_param(proc, ((codage_octal >> 4) & 3), &index);
	reg = read_param(proc, ((codage_octal >> 2) & 3), &index);
	
	if (((codage_octal >> 4) & 3) == IND_CODE)
	{
		i_11 = i_1;
		i_1 = 0;
		i_1 = (i_1 | u_vm->memory[(proc->pc + ((i_11)) + 0) % MEM_SIZE]->data) << 8;
		i_1 = (i_1 | u_vm->memory[(proc->pc + ((i_11)) + 1) % MEM_SIZE]->data) << 8;
		i_1 = (i_1 | u_vm->memory[(proc->pc + ((i_11)) + 2) % MEM_SIZE]->data) << 8;
		i_1 = (i_1 | u_vm->memory[(proc->pc + ((i_11)) + 3) % MEM_SIZE]->data);
	}
	else if (((codage_octal >> 4) & 3) == REG_CODE)
		i_1 = proc->regs[i_1 - 1];
		
	if (((codage_octal >> 4) & 3) == REG_CODE)
		i_2 = proc->regs[i_2 - 1];

	proc->regs[reg - 1] = 0;
	proc->regs[reg - 1] = (proc->regs[reg - 1] | u_vm->memory[(proc->pc + ((i_1 + i_2)) + 0) % MEM_SIZE]->data) << 8;
	proc->regs[reg - 1] = (proc->regs[reg - 1] | u_vm->memory[(proc->pc + ((i_1 + i_2)) + 1) % MEM_SIZE]->data) << 8;
	proc->regs[reg - 1] = (proc->regs[reg - 1] | u_vm->memory[(proc->pc + ((i_1 + i_2)) + 2) % MEM_SIZE]->data) << 8;
	proc->regs[reg - 1] = (proc->regs[reg - 1] | u_vm->memory[(proc->pc + ((i_1 + i_2)) + 3) % MEM_SIZE]->data);

	proc->pc += index;
	
	proc->carry = 1;
	return (1);
}

int handle_label_lfork(t_process *proc) // DONE
{
	t_process 	*last_proc;
	int index;
	int dir;

	index = 1;
	dir = read_param(proc, DIR_CODE, &index);

	last_proc = proc;
	while (last_proc->next)
		last_proc = last_proc->next;
	
	last_proc->next = (t_process*)malloc(sizeof(t_process));

	int i;
	
	i = -1;
	while (++i < REG_NUMBER)
		last_proc->next->regs[i] = proc->regs[i];

	last_proc->next->pc = (proc->pc + (dir)) % MEM_SIZE;
	last_proc->next->carry = proc->carry;

	last_proc->next->cycle_to_run = proc->cycle_to_run + 1;
	last_proc->next->nbr_live = 0;
	last_proc->next->cur_op = NULL;

	last_proc->next->champion = proc->champion;

	last_proc->next->prev = last_proc;
	last_proc->next->next = NULL;

	proc->champion->nb_processes++;

	mvprintw(62 + proc->champion->id, (64 * 3) + 5, "test	8 %d %s %d  %d  %d   ", 
		proc->champion->id, proc->cur_op->name, proc->champion->nb_processes, proc->pc, last_proc->next->pc);
	move(64, 65);
	refresh();

	proc->pc += index;
	return (1);
}

int handle_label_aff(t_process *proc) // DONE
{
	int index;
	int c;

	index = 1;
	c = read_param(proc, REG_CODE, &index);
	
	ft_putchar(proc->regs[c - 1]);

	proc->pc += index;
	
	return (1);
}
