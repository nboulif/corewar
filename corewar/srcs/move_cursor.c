/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:16:20 by nsondag           #+#    #+#             */
/*   Updated: 2019/12/20 16:22:02 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//fichier a supprimer (vu qu'on travaille avec ncurses)
#include "vm_corewar.h"

void	move_up(int positions)
{
	printf("\x1b[%dA", positions);
}

void	move_down(int positions)
{
	printf("\x1b[%dB", positions);
}

void	move_right(int positions)
{
	printf("\x1b[%dC", positions);
}

void	move_left(int positions)
{
	printf("\x1b[%dD", positions);
}

void	move_to(int row, int col)
{
	ft_printf("\x1b[%d;%df", row, col);
}
