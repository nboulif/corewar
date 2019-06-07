/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_f.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __VM_F_H__
# define __VM_F_H__

t_op 	*check_if_operation(unsigned char octet);
void	print_memory(void);
int		init_champions(void);
int		main(int argc, char *argv[]);

int		parse_champion_file(int id);
int		check_valid_magic(void);
int		parse_champion_header(int id);
int		parse_champion_prog(int id);
int		parse_champion(int id, char *argv);
int		parse_champions(int argc, char *argv[]);

int nc_print(unsigned int index);
int check_end(void);
int run_one_cycle(int *champion_alive);
int start_battle(void);

int handle_label_live(t_process *proc);
int handle_label_ld(t_process *proc);
int handle_label_st(t_process *proc);
int handle_label_add(t_process *proc);
int handle_label_sub(t_process *proc);
int handle_label_and(t_process *proc);
int handle_label_or(t_process *proc);
int handle_label_xor(t_process *proc);
int handle_label_zjmp(t_process *proc);
int handle_label_ldi(t_process *proc);
int handle_label_sti(t_process *proc);
int handle_label_fork(t_process *proc);
int handle_label_lld(t_process *proc);
int handle_label_lldi(t_process *proc);
int handle_label_lfork(t_process *proc);
int handle_label_aff(t_process *proc);
#endif