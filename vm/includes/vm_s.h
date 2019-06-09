/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_s.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __VM_S_H__
# define __VM_S_H__

typedef struct			s_champion t_champion;
typedef struct			s_process t_process;

typedef struct			s_process
{
	int32_t			regs[REG_NUMBER];
	uint32_t			pc;
	uint32_t			old_pc;
	uint32_t			carry;

	uint32_t			cycle_to_run;
	uint32_t			nbr_live;
	t_op				*cur_op;

	t_champion			*champion;

	t_process			*prev;
	t_process			*next;
}						t_process;

typedef struct			s_champion
{
	
	int					id;
	uint32_t			last_live;
	uint32_t			total_lives;

	char				*color;
	int					pair_nc_color;
	int					nc_color;

	t_prog				*prog;
	t_process			*processes;
	uint32_t		nb_processes;
	
}						t_champion;

typedef struct			s_mem_status
{
	t_process			*proc;
	uint32_t			nb_process;

	char				*color;
	int					nc_color;
}						t_mem_status;

typedef struct			s_vm
{
	int				fd_input;

	uint8_t			mem_data[MEM_SIZE];
	t_mem_status	mem_stat[MEM_SIZE][1];

	t_champion		**champions;
	uint32_t		nb_champion;
	uint32_t		nb_champion_alive;

	uint32_t		paused;

	uint32_t		total_processes;

	uint32_t		cycle_passed;

	uint32_t		cycle_last_check;

	uint32_t		cycle_to_die;

	uint32_t		nbr_live;

	uint32_t		nbr_check;

	int				(*handlers[16])();
	int32_t			(*hdl_param[16])();
	uint8_t			(*hdl_conv_code_type[16])();

}				t_vm;



#endif