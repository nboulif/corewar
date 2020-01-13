/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polyadic_float.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:13:25 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 11:12:13 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POLYADIC_FLOAT_H
# define POLYADIC_FLOAT_H

# define PF struct s_polyadic_float
# define ULL unsigned long long
# define PFBASE (unsigned long long)1000000000000000000
# define PFMNG struct s_polyadic_float_manager
# define PFPMNG struct s_pf_print_manager

# include <stdlib.h>

typedef struct			s_frac
{
	ULL					fraction;
	unsigned int		left_offset;
}						t_frac;

typedef struct			s_dbl
{
	char				sign;
	unsigned char		normalized;
	int					exponent;
	unsigned char		extrema;
	t_frac				fraction;
}						t_dbl;

typedef struct			s_polyadic_float
{
	ULL					value;
	ULL					inc;
	PF					*right;
	PF					*left;
	int					index;
	PFMNG				*manager;
	unsigned char		size;
}						t_polyadic_float;

typedef struct			s_polyadic_float_manager
{
	char				sign;
	PF					*i_s;
	PF					*i_e;
	PF					*d_s;
	PF					*d_e;
}						t_polyadic_float_manager;

typedef struct			s_pf_print_manager
{
	size_t				index;
	unsigned char		dot_index;
	size_t				more_zeros;
	PF					*cur;
}						t_pf_print_manager;

unsigned char			*store_ldouble_bits(long double in);
unsigned char			*store_double_bits(double in);

PF						*add_right(ULL value, PFMNG *mng);
PF						*add_left(ULL value, PFMNG *mng);
unsigned char			add_inc(PF *pf, PFMNG *mng);
unsigned char			shift_right(PFMNG *mng);
unsigned char			shift_left(PFMNG *mng);

char					extract_float_sign(unsigned char *bits, size_t size);
int						extract_float_exponent(size_t len, size_t offset,
							unsigned char *bits, size_t size);
unsigned char			extract_ldouble_normalized(size_t offset,
							unsigned char *bits, size_t size);
t_frac					extract_float_fraction(size_t len, size_t offset,
							unsigned char *bits, size_t size);

t_dbl					*extract_ldouble_infos(long double in);
t_dbl					*extract_double_infos(double in);

PFMNG					*init_pfmng(t_dbl *dbl);
PF						*init_pf(ULL value, PF *left, PF *right);
void					clean_pfmng(PFMNG *mng);

void					ignore_zeros(PFPMNG *mng);
unsigned char			d_rank_right(PF **cur, unsigned char d_rank,
							unsigned char rank_size);
ULL						generate_base(unsigned char d_rank);
unsigned char			extract_digit(ULL value, unsigned char d_rank);
unsigned char			find_nonzero_digit(PF *cur, unsigned char d_rank,
							unsigned char rank_size);

PFMNG					*pf_manager(t_dbl *dbl);
unsigned char			decode_fraction(t_dbl *dbl, PFMNG *mng, PFMNG *shadow);

#endif
