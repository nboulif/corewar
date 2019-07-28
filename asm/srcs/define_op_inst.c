/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_op_inst.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_op_ch			*define_operation(t_asm *u, t_inst *cur_inst, t_op_ch *cur_op_ch, t_op *op)
{

	if (!op)
	{
		ft_putendl("---NOT OPERATION---");
		return (NULL);
	}
	if (!cur_op_ch)
	{
		cur_op_ch = (t_op_ch*)malloc(sizeof(t_op_ch));
		cur_op_ch->op = op;
		cur_op_ch->prev = NULL;
		cur_op_ch->next = NULL;
		cur_op_ch->index = 0;

		cur_inst->index = u->octal_index;
		cur_inst->ops = cur_op_ch;
		return (cur_op_ch);
	}
	else
	{
		cur_op_ch->next = (t_op_ch*)malloc(sizeof(t_op_ch));
		cur_op_ch->next->op = op;
		cur_op_ch->next->prev = cur_op_ch;
		cur_op_ch->next->next = NULL;
		cur_op_ch->next->index = cur_op_ch->index + 1;

		return (cur_op_ch->next);
	}
}

t_inst *		define_instruction(t_asm *u, t_inst *cur_inst, char *word)
{

	if (!ft_strcmp(cur_inst->name, "main") && !cur_inst->ops)
	{
		ft_strdel(&cur_inst->name);
		cur_inst->name = ft_strdup(word);
		cur_inst->index = u->octal_index;
		return (cur_inst);
	}
	else
	{
		cur_inst->next = (t_inst*)malloc(sizeof(t_inst));
		cur_inst->next->name = ft_strdup(word);
		cur_inst->next->index = u->octal_index;
		cur_inst->next->address = 0;
		cur_inst->next->ops = NULL;
		cur_inst->next->prev = cur_inst;
		cur_inst->next->next = NULL;

		return (cur_inst->next);
	}
}
