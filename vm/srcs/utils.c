/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op 	*check_if_operation(uint8_t octet)
{
	int i;

	i = -1;
	while (++i < 16)
		if (g_op_tab[i].op_code == octet)
			return (&g_op_tab[i]);
	return (NULL);
	
}

void	print_memory(void)
{
	int i;
	int y;

	i = 0;
	while (i < MEM_SIZE)
	{
		y = -1;
		while (++y < 64)
		{
			printf("%s", u_vm->mem_stat[i]->color);
			printf("%.2x ", u_vm->mem_data[i]);
			printf(PF_COLOR_RESET);

			i++;
		}

		printf("\n");
	}
	printf("\n");

}
