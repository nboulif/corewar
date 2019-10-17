/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 14:48:29 by nsondag           #+#    #+#             */
/*   Updated: 2019/10/17 15:11:25 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include <fcntl.h>
# include <stdio.h>
# include "op.h"
# include "libft.h"

# define	SYNTAX	"Syntax error at token [TOKEN]"
# define	END		"END \"(null)\""

typedef struct	s_op t_op;
typedef struct	s_data t_data;
typedef struct	s_label t_label;

typedef struct		s_prog
{
	int				name_found;
	int				comment_found;
	char			*name;
	char			*comment;
	int				l_h; // counter for char in name or comment
	t_op			*op;
	t_data			*list_data;
	t_label			*list_label;
	int				fd;
	char			*full_line;
	char			*line;
	int 			i; // counter char passed in current line
	int				nb_line;
	
	int				prog_size;
	int				debug;

	char			*file_name;

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
	//char	*line;
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

//size_t convert_to_big_endian(size_t x);
int write_file(t_prog *header);

int get_valid_name_comment_loop(t_prog *prog, int max_lenght, char **final_line, int i);
int get_valid_name_comment(t_prog *prog, int max_lenght, char **final_line);
int get_header(t_prog *prog);

int	manage_errors_inexisting_label(t_prog *prog);
int manage_errors_direct(t_prog *prog, int i, int o);
int manage_errors_instruction(t_prog *prog, int i, int o);
int manage_errors_alnum(t_prog *prog, int i, int o);
int manage_errors(t_prog *prog, int i);

t_op	*identify_opc(char *line);
int parse_indirect(t_data *line, int i);
int parse_register(t_data *line, int i);
int parse_direct_char(t_data *line, int i);
int parse_params(t_prog *prog, t_data *line);
t_data	*parse_commands(t_prog *prog);

t_data	*init_data(char *str_params, int nb_line, char *label, char *str_opc);
t_prog	*init_prog(int argc, char **argv);
t_label *update_list_label(t_prog *prog, t_data *data);
int	program_parser(t_prog *prog, t_data	*data);

int print_error_lexical(t_prog *prog, int i);
int print_error_tokken(t_prog *prog, int i, int o, char *error_type);
int print_error(t_prog *prog, int i, int o, char *error_type);

int print_data(t_data *data);
int print_debug(t_prog *prog);

int	get_label(t_prog *prog);

#endif
