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

uint8_t retr_reg_type(void);
uint8_t retr_dir_type(void);
uint8_t retr_ind_type(void);
int32_t read_param_reg(t_process *proc, int *index);
int32_t read_param_ind(t_process *proc, int *index);
int32_t read_param_dir(t_process *proc, int *index);

void			init_handlers(void);
uint32_t		calc_addr(int addr);

t_op 			*check_if_operation(uint8_t octet);
void			print_memory(void);

int				init_champions(void);
int				main(int argc, char *argv[]);

int				parse_champion_file(int id);
int				check_valid_magic(void);
int				parse_champion_header(int id);
int				parse_champion_prog(int id);
int				parse_champion(int id, char *argv);
int				parse_champions(int argc, char *argv[]);

void			init_pairs(void);
int				nc_print_mem(uint32_t index, int fg_color, int bg_color);
int				nc_print_line(int x, int y, int paired_color, char *str);
int				nc_print_player_status(t_champion *champ);
int				nc_print(uint32_t index);

int				check_end(void);
int				run_one_cycle(int *champion_alive);
int				start_battle(void);

int				handle_label_live(t_process *proc);
int				handle_label_ld_lld(t_process *proc);
int				handle_label_st(t_process *proc);
int				handle_label_add_sub(t_process *proc);
int				handle_label_and_or_xor(t_process *proc);
int				handle_label_zjmp(t_process *proc);
int				handle_label_ldi_lldi(t_process *proc);
int				handle_label_sti(t_process *proc);
int				handle_label_forks(t_process *proc);
int				handle_label_aff(t_process *proc);
#endif