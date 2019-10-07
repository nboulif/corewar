/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/22 19:10:30 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int print_data(t_data	*data)
{
	int i;
	int y;
	
	if (data->label)
		printf("%-11d :    %s:\n", data->pc, data->label);
	if (data->op->opc)
	{
		printf("%-5d (%-3d) :        %-10s ", data->pc, data->nb_octet, data->op->name);
		i = 0;
		while(i < data->op->nb_params)
		{
			y = 0;
			while(data->params[i][y] && data->params[i][y] != ' ' && data->params[i][y] != '\t')
				y++;
			printf("%-18.*s", y, data->params[i++]);
		}
		printf("\n");

		printf("%20s %-4d", "", data->op->opc);
		data->op->codage_octal ? printf(" %-6d", data->codage_octal) : printf(" %-6s", "");
		
		i = 0;
		while(i < data->op->nb_params)
		{
			if (((data->codage_octal >> (2 * (3 - i))) & 3) == T_DIR)
			{
				y = 0;
				while (y < 4)
				{
					if (y < (data->op->dir_size ? 2 : 4))
						printf("%-4u", (uint8_t)(data->val_param[i] >> (8 * ((data->op->dir_size ? 1 : 3) - y))));
					else
						printf("    ");
					y++;
				}
				printf("  ");
			}
			else
				printf("%-18d", data->val_param[i]);
			i++;
		}
		printf("\n");
		
		printf("%20s %-4d", "", data->op->opc);
		data->op->codage_octal ? printf(" %-6d", data->codage_octal) : printf(" %-6s", "");
		i = 0;
		while(i < data->op->nb_params)
			printf("%-18d", data->val_param[i++]);
		printf("\n");

		printf("\n");
		data = data->next;
	}
	return (0);
}


int print_debug(t_prog *prog)
{
	t_data	*data;

	printf("Dumping annotated program on standard output\n");
	printf("Program size : %d bytes\n", prog->prog_size);
	printf("Name : \"%s\"\n", prog->name);
	printf("Comment : \"%s\"\n", prog->comment);
	printf("\n");

	data = prog->list_data;
	while (data)
	{
		print_data(data);
		data = data->next;
	}

	return (1);
}
