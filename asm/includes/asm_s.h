/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_s.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __ASM_S_H__
# define __ASM_S_H__

typedef struct	s_inst t_inst;
typedef struct	s_op_ch t_op_ch;
typedef struct	s_op t_op;


typedef struct					s_op
{
	char						*name;
	unsigned int				argc;
	char						argv[3];
	unsigned char				op_code;
	unsigned int				cycle;
	char						*description;
	unsigned char				codage_octal;
	unsigned char				dir_size; // 2 if 1 else 4
}								t_op;

extern t_op 					g_op_tab[17];


typedef struct		s_op_ch
{
	int				index;
	char			**params;
	unsigned int	param_codage;
	t_op			*op;
	t_op_ch			*prev;
	t_op_ch			*next;
}					t_op_ch;

typedef struct	s_inst
{
	char		*name;
	int			index;
	int			address;
	t_op_ch		*ops;
	t_inst		*prev;
	t_inst		*next;
}				t_inst;

typedef struct	s_asm
{
	char		*name;
	char		*comment;
	int			extend;

	t_inst		*insts;


	int			octal_index;
	
	int			fd_input;
	int			fd_output;

}				t_asm;



#endif