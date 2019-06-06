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

typedef struct			s_process t_process;

typedef struct			s_process
{
	unsigned char		regs[REG_NUMBER][REG_SIZE];
	unsigned char		pc;
	unsigned int		carry;
	int					octal_index;

	t_process			*next;
}						t_process;

typedef struct			s_player
{
	
	unsigned char		id;

	t_prog				*prog;
	t_prog				*processes;
	unsigned int		nb_processes;
	
}						t_player;

typedef struct			s_vm
{
	
	unsigned int		magic;

	int					fd_input;
	int					fd_output;

	unsigned int		memory[MEM_SIZE];

	t_player			players[MAX_PLAYERS];

	unsigned int		nb_player;

	unsigned int		cycle;

	unsigned int		check;
	unsigned int		live;

}				t_vm;



#endif