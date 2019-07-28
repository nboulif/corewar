/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_f.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __ASM_F_H__
# define __ASM_F_H__

# include "asm_s.h"

t_op 			*check_if_operation(char *line);
void 			write_program(t_asm *u);

t_op_ch			*define_operation(t_asm *u, t_inst *cur_inst, t_op_ch *cur_op_ch, t_op *op);
t_inst *		define_instruction(t_asm *u, t_inst *cur_inst, char *word);
char			*retrieve_next_world(char **line);
int				parse_params(t_asm *u, t_op_ch *cur_op_ch);
int				parse_next_line(t_asm *u, t_inst *cur_inst, t_op_ch *cur_op_ch, char *line);

int				get_next_line(const int fd, char **line);

char			*retrieve_valid_word(char *param);
t_inst			*check_and_retrieve_valid_inst(t_asm *u, char *word);
int				handle_direct_number(t_asm *u, t_op_ch *cur_op_ch, int nb);
int				handle_direct_label(t_asm *u, char *param, t_op_ch *cur_op_ch);
int				handle_direct_digit(t_asm *u, char *param, t_op_ch *cur_op_ch);
void			handle_direct(t_asm *u, char *param, t_op_ch *cur_op_ch);

int				handle_register(t_asm *u, char *param);
int				handle_number(t_asm *u, char *param);

char			*zap_space_tab(char *line);
int				parse_header(t_asm *u, char **line);
int				handle_extend(t_asm *u);
int				parse_file(t_asm *u);

#endif