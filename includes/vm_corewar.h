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
# include "error_code.h"
/*
** code d'erreur renvoyer
*/
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

typedef struct		s_champs
{
	char			*name;
	char			*comment;
	void			*executable_code;
	size_t			size_name;
	size_t			size_comment;
	size_t			size_executable;
    int				index;
}					t_champs;

typedef struct		s_all
{
	int				*fd;
	t_champs		*champ;
	size_t			nb_champ;
    unsigned int	flag; // si on met un flag pour le visu ou pour activer les threads
}					t_all;

#endif