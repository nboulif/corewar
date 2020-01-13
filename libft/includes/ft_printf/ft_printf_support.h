/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_support.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:17:23 by dabeloos          #+#    #+#             */
/*   Updated: 2019/03/05 18:11:28 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_SUPPORT_H
# define FT_PRINTF_SUPPORT_H
# include <stdarg.h>
# ifdef _WIN32
#  include <io.h>
# else
#  include <unistd.h>
# endif
# include <stdlib.h>
# include <stdint.h>
# include "ft_printf/polyadic_float.h"

typedef struct			s_str
{
	char				*txt;
	size_t				len;
	struct s_str		*next;
	unsigned char		is_raw;
}						t_str;

typedef struct			s_mrk
{
	unsigned char		zero;
	unsigned char		minus;
	unsigned char		plus;
	unsigned char		hashtag;
	unsigned char		blank;
	size_t				len_prefix;
	size_t				mfw;
	unsigned char		arg_precision;
	size_t				precision;
	char				*len_modif;
	size_t				len_len_modif;
	char				type;
	uintmax_t			base;
	unsigned char		error;
}						t_mrk;

t_str					*init_str(t_str *s);
t_str					*clean_str(t_str *s);
void					init_mrk(t_mrk *m);

size_t					size_length_modifier(char *in);
unsigned char			is_flag(char in);
unsigned char			is_number(char in);
char					*pf_strncpy(char *dst, const char *src, size_t len);
unsigned int			ft_atoui_limited(const char *str);

char					*inspect_flags(char *cur, t_mrk *mrk);
char					*inspect_mfw(char *cur, t_mrk *mrk);
char					*inspect_precision(char *cur, t_mrk *mrk);
char					*inspect_length_modifier(char *cur, t_mrk *mrk);
size_t					inspect_arg_type(va_list ap, char *cur, t_str *head,
							t_mrk *mrk);

size_t					handle_c(va_list ap, t_str *head, t_mrk *mrk);
size_t					handle_s(va_list ap, t_str *head, t_mrk *mrk);
size_t					handle_p(va_list ap, t_str *head, t_mrk *mrk);
size_t					handle_d(va_list ap, t_str *head, t_mrk *mrk);
size_t					handle_i(va_list ap, t_str *head, t_mrk *mrk);
size_t					handle_o(va_list ap, t_str *head, t_mrk *mrk);
size_t					handle_u(va_list ap, t_str *head, t_mrk *mrk);
void					handle_u_t(va_list ap, t_str *head, t_mrk *mrk);
size_t					handle_x(va_list ap, t_str *head, t_mrk *mrk);
size_t					handle_x_maj(va_list ap, t_str *head, t_mrk *mrk);
size_t					handle_f(va_list ap, t_str *head, t_mrk *mrk);
size_t					handle_pctg(t_str *head, t_mrk *mrk);

char					*copy_raw_ignore(char *cur, t_str *head, size_t start,
							size_t *len);
char					*copy_raw(char *cur, t_str *head, size_t *len);
char					*decode_identifier(va_list ap, char *cur, t_str *head,
							size_t *len);
t_str					*decode_format(va_list ap, const char *format,
							size_t *len);

void					left_justify(char filler, t_str *head, t_mrk *mrk);
void					right_justify(char filler, t_str *head, t_mrk *mrk);
void					char_left_justify(char filler, t_str *head);
void					char_right_justify(char filler, t_str *head);
void					add_prefix(char *prefix, t_str *head);
char					next_digit(t_str *head);
void					force_prefix(char *prefix, t_str *head);
void					appleft_prefix(char *prefix, t_str *head,
							size_t len_prefix, char ignore);

void					uint_tostr(uintmax_t in, t_str *head, t_mrk *mrk,
							size_t index);
void					int_tostr(intmax_t in, t_str *head, t_mrk *mrk,
							size_t index);
void					uchar_tostr(unsigned char in, t_str *head, t_mrk *mrk);
void					ustr_tostr(char *in, t_str *head, t_mrk *mrk);
void					float_tostr(PFMNG *in, t_str *head, t_mrk *mrk);

void					double_bits_tostr(double in, t_str *head);
void					ldouble_bits_tostr(long double in, t_str *head);

char					symb_lc(size_t index);
char					symb_uc(size_t index);

char					*str_lst_join(t_str *slst, size_t len);

void					main_recursion(PFMNG *in, t_str *head, t_mrk *mrk,
							PFPMNG mng);

unsigned char			pf_extrema(t_dbl *dbl, t_str *head, t_mrk *mrk);

unsigned char			pf_boot_lf(long double in, t_str *head, t_mrk *mrk);
unsigned char			pf_boot_f(double in, t_str *head, t_mrk *mrk);

unsigned char			zeros_or_round(PFMNG *in, t_mrk *mrk, PFPMNG *mng);

#endif
