/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 15:30:09 by nsondag           #+#    #+#             */
/*   Updated: 2019/11/08 16:28:11 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <fcntl.h>
# include <stdio.h>
# include "op.h"
# include "error.h"
# include "../libft/libft.h"

# define SYNTAX			"Syntax error at token [TOKEN]"
# define END			"END \"(null)\""
# define USAGE1			"Usage: ./asm_res [-a] <sourcefile.s>\n"
# define USAGE2			"    -a : Instead of creating a .cor file, "
# define USAGE3			"outputs a stripped and annotated version "
# define USAGE4			"of the code to the standard output\n"
# define PARAM			"Invalid parameter"
# define TYPE_DIR		"type direct for instruction"
# define TYPE_INDIR		"type indirect for instruction"
# define TYPE_REG		"type register for instruction"
# define NO_LABEL		"No such label"
# define DEREF			"while attempting to dereference token"
# define EXTENSION		".cor"
# define OK				0
# define ERROR			1

typedef struct s_data	t_data;
typedef struct s_op		t_op;

struct					s_op
{
	char				*name;
	int					nb_params;
	char				params[3];
	int					opc;
	int					cycles;
	char				*comment;
	unsigned char		codage_octal;
	int					dir_size;
};

struct					s_data
{
	char				*line;
	int					pc;
	char				*label;
	int					nb_octet;
	int					nb_line;
	t_op				*op;
	char				**params;
	int					i;
	int					val_param[3];
	int					codage_octal;
	t_data				*next;
};

/*
** int					l_h; // counter for char in name or comment
** int					i; // counter char passed in current line
*/

typedef struct			s_prog
{
	int					debug;
	int					nb_line;
	char				*name;
	char				*comment;
	t_data				*list_data;
	int					fd;
	int					l_h;
	t_op				*op;
	char				*line;
	int					i;
	int					prog_size;
	char				*file_name;
}						t_prog;

extern					t_op g_op_tab[17];

int						get_header(t_prog *prog);
int						write_file(t_prog *header);

int						get_valid_name_comment(t_prog *prog, int max_lenght,
						char **final_line);

int						manage_errors_inexisting_label(t_data *data,
						int label_error_line);

int						parse_register(t_prog *prog, t_data *line, int i);
int						parse_non_register(t_prog *prog, t_data *d, int i,
						int type);
int						parse_params(t_prog *prog, t_data *line);
t_data					*parse_label(t_prog *prog, int *skip_len);
t_data					*parse_opc(t_prog *prog, int skip_len, char *label);

t_data					*init_data(t_prog *p, char *str_params, char *label,
						t_op *op);
t_data					*init_data_label(t_prog *p, char *label);
t_prog					*init_prog(int argc, char **argv);

t_data					*parse_commands(t_prog *prog);
int						program_parser(t_prog *prog, t_data *data,
						t_data *old_data);

int						print_data(t_data *data);
int						print_debug(t_prog *prog);

char					*skip_chars2(char *s, char *charset);
int						skip_chars(char *line, int *i, char *charset);
int						skip_until(char *line, int *i, char *charset);

int						count_digit_string(char *s);

int						tab_len(char **tab);
t_data					*get_pc(t_prog *prog, t_data *tmp_data, t_data *data);
t_op					*identify_opc(char *line);
int						valid_char(const char *str, int base);

int						err_default(t_prog *p, int error_nb);
int						err_lexical(t_prog *p, int error_nb, int i);
int						err_malloc(char *str, int nb_line);
int						err_param_type(t_prog *p, char *str, int indice);
int						err_missing_quotes(t_prog *p, char *error_type,
						int start);
int						err_header_divers(t_prog *p, int error_nb,
						char *error_type);

int						free_one_data(t_data *data);
int						free_data(t_data *begin_data);
int						free_data_params(t_data *d, int i);
int						free_str(char *str);
int						free_prog(t_prog *p);

#endif
