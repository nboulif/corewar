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
	unsigned int		regs[REG_NUMBER];
	unsigned int		pc;
	unsigned int		old_pc;
	unsigned int		carry;

	unsigned int		cycle_to_run;
	unsigned int		nbr_live;
	t_op				*cur_op;

	t_champion			*champion;

	t_process			*prev;
	t_process			*next;
}						t_process;

typedef struct			s_champion
{
	
	unsigned char		id;
	unsigned int		last_live;
	unsigned int		total_lives;

	char				*color;
	int					pair_nc_color;
	int					nc_color;

	t_prog				*prog;
	t_process			*processes;
	unsigned int		nb_processes;
	
}						t_champion;

typedef struct			s_memory
{
	unsigned char		data;
	t_process			*proc;
	int					nb_process;

	char				*color;
	int					nc_color;
}						t_memory;

typedef struct			s_vm
{
	int					fd_input;

	t_memory			memory[MEM_SIZE][1];

	t_champion			**champions;
	unsigned int		nb_champion;
	unsigned int		nb_champion_alive;

	unsigned int		total_processes;

	unsigned int		cycle_passed;

	unsigned int		cycle_last_check;

	unsigned int		cycle_to_die;

	unsigned int		nbr_live;

	unsigned int		nbr_check;

	int					(*handlers[16])();

}				t_vm;



#endif