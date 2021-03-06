/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:34:49 by nsondag           #+#    #+#             */
/*   Updated: 2019/12/20 16:43:59 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

unsigned int		g_flags[256] = {0};
char				*g_flags_syn[256] = {NULL};

int					g_ncurse_color[256] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

t_op	g_op_tab[17] =
{
	{NULL, 0, 0, {0}, {0}, {0}, 0, 0, 0, 0, 0},
	{op_live, "live", 1, {T_DIR}, {F_DIR}, {0}, 1, 10, "alive", 0, 0},
	{op_ld, "ld", 2, {T_DIR | T_IND, T_REG},
		{F_DIR | F_IND, F_REG}, {0}, 2, 5, "load", 1, 0},
	{op_st, "st", 2, {T_REG, T_IND | T_REG},
		{F_REG, F_IND | F_REG}, {0}, 3, 5, "store", 1, 0},
	{op_add, "add", 3, {T_REG, T_REG, T_REG},
		{F_REG, F_REG, F_REG}, {0}, 4, 10, "addition", 1, 0},
	{op_sub, "sub", 3, {T_REG, T_REG, T_REG},
		{F_REG, F_REG, F_REG}, {0}, 5, 10, "soustraction", 1, 0},
	{op_and, "and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		{F_REG | F_DIR | F_IND, F_REG | F_IND | F_DIR, F_REG}, {0}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{op_or, "or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		{F_REG | F_IND | F_DIR, F_REG | F_IND | F_DIR, F_REG}, {0}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{op_xor, "xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		{F_REG | F_IND | F_DIR, F_REG | F_IND | F_DIR, F_REG}, {0}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{op_zjmp, "zjmp", 1, {T_DIR}, {T_DIR}, {0}, 9, 20, "jump if zero", 0, 1},
	{op_ldi, "ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		{F_REG | F_DIR | F_IND, F_DIR | F_REG, F_REG}, {0}, 10, 25,
		"load index", 1, 1},
	{op_sti, "sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		{F_REG, F_REG | F_DIR | F_IND, F_DIR | F_REG}, {0}, 11, 25,
		"store index", 1, 1},
	{op_fork, "fork", 1, {T_DIR}, {F_DIR}, {0}, 12, 800, "fork", 0, 1},
	{op_lld, "lld", 2, {T_DIR | T_IND, T_REG}, {F_DIR | F_IND, F_REG},
		{0}, 13, 10, "long load", 1, 0},
	{op_lldi, "lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		{F_REG | F_DIR | F_IND, F_DIR | F_REG, F_REG}, {0}, 14, 50,
		"long load index", 1, 1},
	{op_longfork, "lfork", 1, {T_DIR}, {F_DIR},
		{0}, 15, 1000, "long fork", 0, 1},
	{op_aff, "aff", 1, {T_REG}, {F_REG}, {0}, 16, 2, "aff", 1, 0}
};
