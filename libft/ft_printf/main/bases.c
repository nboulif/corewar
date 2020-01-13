/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bases.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 15:22:29 by dabeloos          #+#    #+#             */
/*   Updated: 2019/02/25 12:29:47 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			symb_lc(size_t index)
{
	static const char	base[] = "0123456789abcdef";

	if (index > 16)
		return (0);
	return (base[index]);
}

char			symb_uc(size_t index)
{
	static const char	base[] = "0123456789ABCDEF";

	if (index > 16)
		return (0);
	return (base[index]);
}
