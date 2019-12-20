/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:16:02 by nsondag           #+#    #+#             */
/*   Updated: 2019/12/20 16:16:03 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm_corewar.h"

void				config_flags(void)
{
	flags['d'] = FLAG_DUMP;
	flags['n'] = FLAG_NUMBER;
	flags['t'] = FLAG_THREAD;
	flags['v'] = FLAG_VISU;
	flags['r'] = FLAG_RESUME;
	flags['c'] = FLAG_CYCLE;
	flags['x'] = FLAG_DEATH;
	flags['L'] = FLAG_LIVE;
	flags['D'] = FLAG_DUMP64;
}

void				config_flags_syn(void)
{
	flags_syn['d'] = "dump";
}
