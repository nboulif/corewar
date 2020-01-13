/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_boot.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 12:36:10 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:31:45 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	pf_boot(t_dbl *dbl, t_str *head, t_mrk *mrk)
{
	unsigned char				pf_fail;
	t_polyadic_float_manager	*mng;

	if ((pf_fail = pf_extrema(dbl, head, mrk)))
		return ((pf_fail == 2) ? 0 : 1);
	mng = pf_manager(dbl);
	if (mng == NULL)
		return (0);
	float_tostr(mng, head, mrk);
	clean_pfmng(mng);
	return (1);
}

unsigned char	pf_boot_lf(long double in, t_str *head, t_mrk *mrk)
{
	t_dbl			*dbl;

	if (!(dbl = extract_ldouble_infos(in)))
		return (0);
	return (pf_boot(dbl, head, mrk));
}

unsigned char	pf_boot_f(double in, t_str *head, t_mrk *mrk)
{
	t_dbl			*dbl;

	if (!(dbl = extract_double_infos(in)))
		return (0);
	return (pf_boot(dbl, head, mrk));
}
