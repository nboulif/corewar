/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 17:50:32 by nsondag           #+#    #+#             */
/*   Updated: 2019/10/23 12:33:29 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_params_net(t_data *data, int i, int y)
{
	printf("\n%20s%-3d", "", data->op->opc);
	data->op->codage_octal ? printf(" %-6d",
		data->codage_octal) : printf(" %-6s", "");
	i = 0;
	while (i < data->op->nb_params)
	{
		if (((data->codage_octal >> (2 * (3 - i))) & 3) == T_DIR)
		{
			y = 0;
			while (y < 4)
			{
				if (y < (data->op->dir_size ? 2 : 4))
					printf("%-4u", (uint8_t)(data->val_param[i]
						>> (8 * ((data->op->dir_size ? 1 : 3) - y))));
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
}

void	print_params_brut(t_data *data)
{
	int i;

	printf("\n%20s%-3d", "", data->op->opc);
	data->op->codage_octal ? printf(" %-6d",
		data->codage_octal) : printf(" %-6s", "");
	i = 0;
	while (i < data->op->nb_params)
		printf("%-18d", data->val_param[i++]);
}

void	print_params_as_read(t_data *data, int i, int y)
{
	int l;

	if (((data->codage_octal >> (2 * (3 - i))) & 3) == T_DIR
		&& data->params[i][y] == DIRECT_CHAR
		&& data->params[i][y + 1] == LABEL_CHAR)
	{
		l = 0;
		while (data->params[i][l + y] && data->params[i][l + y] != ' ' &&
			data->params[i][l + y] != '\t')
			l++;
		printf("%-18.*s", l, (data->params[i] + y));
	}
	else
	{
		l = (int)count_digit(data->val_param[i]) -
			(data->val_param[i] < 0 ? 1 : 0);
		if (((data->codage_octal >> (2 * (3 - i))) & 3) == T_REG)
			printf("r%-17.*d", l, data->val_param[i]);
		else if (((data->codage_octal >> (2 * (3 - i))) & 3) == T_IND)
			printf("%-18.*d", l, data->val_param[i]);
		else if (((data->codage_octal >> (2 * (3 - i))) & 3) == T_DIR)
			printf("%%%-17.*d", l, data->val_param[i]);
	}
}

int		print_data(t_data *data)
{
	int i;
	int y;

	if (data->label)
		printf("%-11d:    %s:\n", data->pc, data->label);
	if (data->op && data->op->opc)
	{
		printf("%-5d(%-3d) :        %-10s", data->pc,
			data->nb_octet, data->op->name);
		i = 0;
		y = 0;
		skip_chars(data->params[i], &y, " \t");
		while (i < data->op->nb_params)
			print_params_as_read(data, i++, y);
		print_params_net(data, 0, 0);
		print_params_brut(data);
		printf("\n\n");
		data = data->next;
	}
	return (0);
}

int		print_debug(t_prog *prog)
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
