/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:48:29 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/14 16:25:53 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <fcntl.h>
# include <stdio.h>


typedef struct		s_prog
{
	char	*name;
	char	*comment;
}					t_prog;

typedef struct s_op
{
	char	*name;
	int		nb_params;
	char	params[3];
	int		opc;
	int		cycles;
	char	*comment;
	int		codage_octal;
	int		dir_size;
}				t_op;

typedef struct	s_line
{
	int		nb_line;
	char	*label;
	int		opc;
	int		nb_params;
	char	*params;
	char	*param1;
	char	*param2;
	char	*param3;
}				t_line;

extern t_op g_op_tab[17];

int magic_number(t_prog *header);

#endif
