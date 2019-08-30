/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:48:29 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/22 19:02:16 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <fcntl.h>
# include <stdio.h>
# include "op.h"
# include "libft.h"


typedef struct	s_op t_op;
typedef struct	s_data t_data;
typedef struct	s_label t_label;

typedef struct		s_prog
{
	int				name_found;
	int				comment_found;
	char			*name;
	char			*comment;
	int				l_h;
	t_op			*op;
	t_data			*list_data;
	t_label			*list_label;
	int				fd;
	char			*line;
	int				nb_line;
}					t_prog;


typedef struct s_op
{
	char			*name;
	int				nb_params;
	char			params[3];
	int				opc;
	int				cycles;
	char			*comment;
	unsigned char	codage_octal;
	int				dir_size;
}				t_op;

typedef struct	s_data
{
	int		pc;
	char	*label;
	int		nb_octet;
	int		nb_line;
	t_op	*op;
	char	**params;
	int		val_param[3];
	int		codage_octal;
	t_data	*next;
}				t_data;

typedef struct	s_label
{
	char	*label;
	int 	pc;
	t_label	*next;
}				t_label;

extern t_op g_op_tab[17];

int		get_header(t_prog *prog);	
int		magic_number(t_prog *header);

int		manage_errors(t_prog *prog, int i);

int		print_error(t_prog *prog, int i, int o, char *error_type);
int		print_error_tokken(t_prog *prog, int i, int o, char *error_type);
int		print_error_lexical(t_prog *prog, int i);

#endif
