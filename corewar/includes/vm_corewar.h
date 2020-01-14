/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_corewar.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:25:18 by dabeloos          #+#    #+#             */
/*   Updated: 2020/01/11 16:43:42 by nsondag          ###   ########.fr       */
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

/*
** ncurses
*/

# include <ncurses.h>

# define NC_KEY_SPACE			32
# define NC_KEY_Q				113
# define NC_KEY_W				119
# define NC_KEY_E				101
# define NC_KEY_R				114
# define NC_KEY_ENTER			10

# define NC_LINE_PAUSED			1
# define NC_LINE_MAX_CYCLE		4
# define NC_LINE_CYCLE_PASSED	7
# define NC_LINE_PROC_PASSED	8
# define NC_LINE_PLAYER_STATUS	11
# define NC_LINE_CYCLE_TO_DIE	35
# define NC_LINE_RESULT			50

# include "op.h"

# define SIZE_BUFF			2800
# define SIZE_BLOCK_MEM		50000
# define FLAG_DUMP			1
# define FLAG_THREAD		2
# define FLAG_VISU			4
# define FLAG_NUMBER		8
# define FLAG_RESUME		16
# define FLAG_CYCLE			32
# define FLAG_DEATH			64
# define FLAG_DUMP64		128
# define FLAG_LIVE			256

# define B1					0x000000ff
# define B2 				0x0000ff00
# define B3 				0x00ff0000
# define B4 				0xff000000

typedef struct s_process	t_process;
typedef struct s_all		t_all;
typedef struct s_op			t_op;

struct						s_op
{
	void					(*op)(t_all *all, t_process *proc);
	char					*name;
	int						nb_params;
	char					type_of_params[3];
	char					flags_params[3];
	int						params[3];
	int						opc;
	int						cycles;
	char					*comment;
	unsigned char			codage_octal;
	unsigned char			dir_size;
};

typedef struct				s_champ
{
	char					*name;
	char					*comment;
	void					*exec_code;
	int						i_exec_code;
	size_t					size_name;
	size_t					size_comment;
	size_t					size_exec;
	int						index;
	int						index_player;
	unsigned char			flag_index;
	int						alive;
	int						nb_live;
	int						nb_live_cur_period;
	int						last_live;
}							t_champ;

struct						s_process
{
	t_champ					*origin_champ;
	int						step_in_exec;
	int						flag_live;
	int						wait;
	int						reg[REG_NUMBER];
	int						pc;
	int						carry;
	t_op					op;
	int						index;
	int						last_live;
	struct s_process		*next;
};

typedef struct				s_map
{
	char					*character;
	int						*color_in_map;
}							t_map;

struct						s_all
{
	t_map					map;
	size_t					nb_champ;
	int						nb_process;
	unsigned int			flag;
	t_champ					champ[4];
	t_process				*stack_proc;
	int						cycle_to_die;
	int						cycles_before_exit;
	t_champ					*last_player_alive;
	int						nb_live;
	int						nb_alive;
	int						nb_check;
	int						max;
	int						total_cycle;

	int						max_cycle_by_sec;
	int						nc_paused;
};

/*
** global variable
*/

extern unsigned int			g_flags[256];
extern char					*g_flags_syn[256];
extern t_op					g_op_tab[17];
extern int					g_ncurse_color[256];

/*
** utils
*/

void						init_all(t_all *all);
void						set_indexes(t_all *all);
int							is_a_process(t_all *all, int pc);
int							calcul_new_pc_idx(int pc, int deplacement);
int							calcul_new_pc(int pc, int deplacement);
void						config_flags_and_flags_syn(void);
int							ft_realloc(void **tab, int *size_av, int
		new_size_ap, size_t type_size);
int							read_all(char **str, int fd);
void						print_error_and_exit(int type_of_error);
int							check_index(char *index);
int							rev_int_byte(int nbr);
void						move_pc(int *pc, int incr);
t_champ						*get_champ(int index, t_all *all);
void						print_bit(char nb);
int							read_int_in_map(t_all *all, int pc);
void						change_color(t_all *all, t_process *proc, int i);
void						handle_dump(int *i, int argc,
		char **argv, t_all *all);
int							is_valid_flag(char *flag);

/*
** visu ncurses
*/

void						simple_hexdump(t_all *all, int bytes_per_line);
void						ncurses_print_player_info(t_all *all);
void						ncurses_print_info(t_all *all);
void						ncurses_manage_pause(t_all *all);
void						ncurses_event_handler(t_all *all);
void						ncurses_print_map_square(t_all *all);
void						ncurses_print_map_square_v2(t_all *all);
void						ncurses_print_screen(t_all *all);
void						init_ncurses(void);

/*
** parse_champ
*/

int							handle_flag(int *i, int argc,
		char **argv, t_all *all);
void						parse_champ(t_all *all, char *index, char *file);

/*
** init_vm
*/

void						init_vm(t_all *all);

/*
**	qsort_proc
*/

void						qsort_champ(t_champ *champ,
		int start_ind, int size);

/*
**	visu
*/

void						*check_pause(void *arg);

/*
** vm
*/

void						vm(t_all *all);
int							check_ctd(t_all *all);
void						make_action_and_visu(t_all *all);

/*
** op
*/

void						op_live(t_all *all, t_process *proc);
void						op_add(t_all *all, t_process *proc);
void						op_aff(t_all *all, t_process *proc);
void						op_and(t_all *all, t_process *proc);
void						op_fork(t_all *all, t_process *proc);
void						op_ld(t_all *all, t_process *proc);
void						op_lld(t_all *all, t_process *proc);
void						op_ldi(t_all *all, t_process *proc);
void						op_longfork(t_all *all, t_process *proc);
void						op_xor(t_all *all, t_process *proc);
void						op_or(t_all *all, t_process *proc);
void						op_zjmp(t_all *all, t_process *proc);
void						op_sub(t_all *all, t_process *proc);
void						op_sti(t_all *all, t_process *proc);
void						op_st(t_all *all, t_process *proc);
void						op_lldi(t_all *all, t_process *proc);

/*
** op_utils
*/

void						config_arg_binary_op(t_all *all,
		t_process *proc, int pc_to_read);
void						give_value_of_larg(t_all *all,
		t_process *proc, int pc, int index);
void						give_value_of_arg(t_all *all,
		t_process *proc, int pc, int index);
int							value_of_arg(t_all *all,
		t_process *proc, int pc, int index);
t_process					*proc_alloc(int mode);

/*
** parse_arg_op
*/

int							parse_arg_op(t_all *all, t_process *proc);

#endif
