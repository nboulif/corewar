/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_corewar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:25:18 by dabeloos          #+#    #+#             */
/*   Updated: 2019/12/18 17:18:13 by nsondag          ###   ########.fr       */
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

# define SIZE_BUFF	2800

# define FLAG_DUMP		1
# define FLAG_THREAD	2
# define FLAG_VISU		4
# define FLAG_NUMBER	8
# define FLAG_RESUME	16
# define FLAG_CYCLE		32
# define FLAG_DEATH		64
# define FLAG_DUMP64	128
# define FLAG_LIVE		256

#define B1 0x000000ff
#define B2 0x0000ff00
#define B3 0x00ff0000
#define B4 0xff000000

typedef struct s_process	t_process;
typedef struct s_all		t_all;

typedef struct s_op
{
	void			(*op)(t_all *all, t_process *proc);
	char			*name;
	int				nb_params;
	char			type_of_params[3];
	char			flags_params[3];
	int				params[3];
	int				opc;
	int				cycles;
	char			*comment;
	unsigned char	codage_octal;
	unsigned char	dir_size;
}				t_op;

typedef struct		s_champ
{
	char			*name;
	char			*comment;
	void			*exec_code;
	int				i_exec_code;
	size_t			size_name;
	size_t			size_comment;
	size_t			size_exec;
    int				index;
	int				index_player;
	unsigned char	flag_index;
	int				alive;
	int				nb_live;
}					t_champ;

typedef struct		s_process
{
	t_champ				*origin_champ;
	int					step_in_exec;
	int					flag_live;
	int					wait;
	// les registres
	int					reg[REG_NUMBER];
	int					pc;
	int					carry;
	// current operation
	t_op				op;
	int					index;
	int					last_live;
	struct s_process	*next;
}					t_process;

typedef struct		s_map
{
	char			*character;
	char			**color_in_map;
}					t_map;



typedef struct		s_all
{
	t_map			map;
	// char			*map;
	// char			*color_in_map;
	size_t			nb_champ;
	int				nb_process;
    unsigned int	flag; // si on met un flag pour le visu ou pour activer les threads
	t_champ			champ[4];
	// t_array			*stack_proc;
	t_process		*stack_proc;
	int				cycle_to_die;
	int				cycles_before_exit;
	t_champ			*last_player_alive;
	int				nb_live;
	int				nb_alive;
	int				nb_check;
	int				max;
	int				total_cycle;
}					t_all;

/*
** global variable
*/

extern unsigned int		flags[256];
extern char				*flags_syn[256];
extern t_op				op_tab[17];
extern char				*text_color[256];
extern char				*background_color[256];

/*
** utils
*/

void		config_flags(void);
void		config_flags_syn(void);
int			ft_realloc(void **tab, int *size_av,
					int new_size_ap, size_t type_size);
int			read_all(char **str, int fd);
void		print_error_and_exit(int type_of_error);
int			check_index(char *index);
int			rev_int_byte(int nbr);
void		move_pc(int *pc, int incr);
t_champ		*get_champ(int index, t_all *all);
void		hexdump_map_square(t_all *all);
void		simple_hexdump(t_all *all);
void		print_bit(char nb);
void		moveTo(int row, int col);
int			read_int_in_map(t_all *all, int pc);
void		change_color(t_all *all, t_process *proc, int i);

/*
** parse_champ 
*/

void		parse_champ(t_all *all, char *index, char *file);

/*
** init_vm
*/

void		init_vm(t_all *all);

/*
** vm
*/

void		vm(t_all *all);

/*
** op
*/

void    	op_live(t_all *all, t_process *proc);
void    	op_add(t_all *all, t_process *proc);
void    	op_aff(t_all *all, t_process *proc);
void    	op_and(t_all *all, t_process *proc);
void    	op_fork(t_all *all, t_process *proc);
void    	op_ld(t_all *all, t_process *proc);
void    	op_lld(t_all *all, t_process *proc);
void    	op_ldi(t_all *all, t_process *proc);
void    	op_longfork(t_all *all, t_process *proc);
void    	op_xor(t_all *all, t_process *proc);
void    	op_or(t_all *all, t_process *proc);
void    	op_zjmp(t_all *all, t_process *proc);
void    	op_sub(t_all *all, t_process *proc);
void    	op_sti(t_all *all, t_process *proc);
void    	op_st(t_all *all, t_process *proc);
void    	op_lldi(t_all *all, t_process *proc);

/*
** op_utils
*/

void		config_arg_binary_op(t_all *all, t_process *proc, int pc_to_read);
void		give_value_of_larg(t_all *all, t_process *proc, int pc, int index);
void		give_value_of_arg(t_all *all, t_process *proc, int pc, int index);
int			value_of_arg(t_all *all, t_process *proc, int pc, int index);
t_process	*proc_alloc(int mode);

/*
** parse_arg_op
*/

int			parse_arg_op(t_all *all, t_process *proc);

#endif
