/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 15:08:16 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/13 20:05:14 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include <stdio.h>
# include "libft.h"

int one_param_reg(char *params, int opc)
{
	if (params[1] == ":")
		printf("label\n");
	else
		printf("no label\n");
	return (0);
}
