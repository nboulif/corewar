/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __ASM_H__
# define __ASM_H__

# include <limits.h>
# include <fcntl.h>

# include "op.h"
# include "../libft/libft.h"

# define BUFF_SIZE 10000


typedef struct	s_inst t_inst;
typedef struct	s_op_ch t_op_ch;

typedef struct	s_op_ch
{
	int			index;
	char		**params;
	t_op		*op;
	t_op_ch		*prev;
	t_op_ch		*next;
}				t_op_ch;

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

typedef struct	s_gnl
{
	char	buf[BUFF_SIZE + 1];
	char	*r[OPEN_MAX];
	int		ret;
	int		len;
	int		n;
}				t_gnl;

int				get_next_line(const int fd, char **line);

#endif