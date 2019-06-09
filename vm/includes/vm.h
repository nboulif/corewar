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
# include <stdint.h>

# include <ncurses.h>

# include "op.h"
# include "corewar_s.h"
# include "vm_s.h"
# include "vm_f.h"
# include "../libft/libft.h"


# define PF_COLOR_RED				"\x1b[31m"
# define PF_COLOR_GREEN 			"\x1b[32m"
# define PF_COLOR_YELLOW			"\x1b[33m"
# define PF_COLOR_BLUE				"\x1b[34m"
# define PF_COLOR_MAGENTA			"\x1b[35m"
# define PF_COLOR_CYAN				"\x1b[36m"
# define PF_COLOR_WHITE				"\x1b[37m"
# define PF_COLOR_RESET				"\x1b[0m"

# define PF_COLOR_PLAYER_1			PF_COLOR_RED
# define PF_COLOR_PLAYER_2			PF_COLOR_GREEN
# define PF_COLOR_PLAYER_3			PF_COLOR_BLUE
# define PF_COLOR_PLAYER_4			PF_COLOR_YELLOW

# define NC_COLOR_BLACK			0
# define NC_COLOR_RED			1
# define NC_COLOR_GREEN 		2
# define NC_COLOR_YELLOW		3
# define NC_COLOR_BLUE			4
# define NC_COLOR_MAGENTA		5
# define NC_COLOR_CYAN			6
# define NC_COLOR_WHITE			7

# define NC_COLOR_PLAYER_1		NC_COLOR_RED
# define NC_COLOR_PLAYER_2		NC_COLOR_GREEN
# define NC_COLOR_PLAYER_3		NC_COLOR_GREEN
# define NC_COLOR_PLAYER_4		NC_COLOR_YELLOW

# define NC_KEY_SPACE			32
# define NC_KEY_Q				113
# define NC_KEY_W				119
# define NC_KEY_E				101
# define NC_KEY_R				114
# define NC_LINE_POSE			5
# define NC_LINE_CYCLE_PASSED	1
# define NC_LINE_SLEEP			2
# define NC_LINE_PLAYER_STATUS	10

# include <stdio.h>


# define BUFF_SIZE 10000

extern t_op 					g_op_tab[17];
extern t_vm 					*u_vm;

typedef struct	s_gnl
{
	char	buf[BUFF_SIZE + 1];
	char	*r[OPEN_MAX];
	int		ret;
	int		len;
	int		n;
}				t_gnl;

#endif