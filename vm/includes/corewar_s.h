/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_s.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __COREWAR_S_H__
# define __COREWAR_S_H__

typedef struct	s_inst t_inst;
typedef struct	s_op_ch t_op_ch;
typedef struct	s_op t_op;

typedef struct					s_op
{
	char						*name;
	uint32_t				argc;
	uint8_t						argv[3];
	uint8_t				op_code;
	uint32_t				cycle;
	char						*description;
	uint8_t				codage_octal;
	uint8_t				dir_size; // 2 if 1 else 4
}								t_op;



typedef struct					s_op_ch
{
	int							index;
	char						**params;
	uint32_t				param_codage;
	t_op						*op;
	t_op_ch						*prev;
	t_op_ch						*next;
}								t_op_ch;

typedef struct					s_inst
{
	char						*name;
	int							index;
	int							address;
	t_op_ch						*ops;
	t_inst						*prev;
	t_inst						*next;
}								t_inst;

typedef struct					s_prog
{
	char						prog_name[PROG_NAME_LENGTH + 1];
	char						comment[COMMENT_LENGTH + 1];

	uint32_t				prog_size;
	int							extend;
	t_inst						*insts;
	uint8_t					*prog;

}								t_prog;



#endif