#include "vm_corewar.h"

unsigned int		flags[256] = {0};
char				*flags_syn[256] = {NULL};

t_op    op_tab[17] =
{
	{NULL, 0, 0, {0}, {0}, 0, 0, 0, 0, 0},
	{op_live, "live", 1, {T_DIR}, {0}, 1, 10, "alive", 0, 0},
	{NULL, "ld", 2, {T_DIR | T_IND, T_REG}, {0}, 2, 5, "load", 1, 0},
	{NULL, "st", 2, {T_REG, T_IND | T_REG}, {0}, 3, 5, "store", 1, 0},
	{NULL, "add", 3, {T_REG, T_REG, T_REG}, {0}, 4, 10, "addition", 1, 0},
	{NULL, "sub", 3, {T_REG, T_REG, T_REG}, {0}, 5, 10, "soustraction", 1, 0},
	{NULL, "and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, {0}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{NULL, "or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, {0}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{NULL, "xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, {0}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{NULL, "zjmp", 1, {T_DIR}, {0}, 9, 20, "jump if zero", 0, 1},
	{NULL, "ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, {0}, 10, 25,
		"load index", 1, 1},
	{NULL, "sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, {0}, 11, 25,
		"store index", 1, 1},
	{NULL, "fork", 1, {T_DIR}, {0}, 12, 800, "fork", 0, 1},
	{NULL, "lld", 2, {T_DIR | T_IND, T_REG}, {0}, 13, 10, "long load", 1, 0},
	{NULL, "lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, {0}, 14, 50,
		"long load index", 1, 1},
	{NULL, "lfork", 1, {T_DIR}, {0}, 15, 1000, "long fork", 0, 1},
	{NULL, "aff", 1, {T_REG}, {0}, 16, 2, "aff", 1, 0}
};