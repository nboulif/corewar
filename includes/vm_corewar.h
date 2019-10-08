/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_corewar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:25:18 by dabeloos          #+#    #+#             */
/*   Updated: 2019/10/08 15:25:20 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_COREWAR_H
# define VM_COREWAR_H
# include "libft.h"
/*
** read
** lseek
** write
** close
** 
*/
# include <unistd.h>
/*
** malloc
** realloc
** free
** exit
*/
# include <stdlib.h>
/*
** open
*/
# include <fcntl.h>
/*
** perror
*/
# include <stdio.h>
/*
** strerror
*/
# include <string.h>
/*
** errno
*/
# include <errno.h>
# include "op.h"

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

#endif