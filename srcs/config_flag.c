/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:16:02 by nsondag           #+#    #+#             */
/*   Updated: 2019/12/20 16:49:20 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void				config_flags(void)
{
	g_flags['d'] = FLAG_DUMP;
	g_flags['n'] = FLAG_NUMBER;
	g_flags['t'] = FLAG_THREAD;
	g_flags['v'] = FLAG_VISU;
	g_flags['r'] = FLAG_RESUME;
	g_flags['c'] = FLAG_CYCLE;
	g_flags['x'] = FLAG_DEATH;
	g_flags['L'] = FLAG_LIVE;
	g_flags['D'] = FLAG_DUMP64;
}

void				config_flags_syn(void)
{
	g_flags_syn['d'] = "dump";
}
