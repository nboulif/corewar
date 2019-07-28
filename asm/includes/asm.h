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
# include "corewar_s.h"
# include "asm_s.h"
# include "asm_f.h"
# include "../libft/libft.h"

# define BUFF_SIZE 10000

extern t_op 					g_op_tab[17];

typedef struct	s_gnl
{
	char	buf[BUFF_SIZE + 1];
	char	*r[OPEN_MAX];
	int		ret;
	int		len;
	int		n;
}				t_gnl;

#endif