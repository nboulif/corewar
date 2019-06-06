/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_f.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboulif <nboulif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 23:59:12 by nboulif           #+#    #+#             */
/*   Updated: 2019/03/05 00:41:45 by nboulif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef __VM_F_H__
# define __VM_F_H__

int		init_vm();
int		run_vm();
int		parse_player(int id);
int		parse_champion(int id, char *argv);
int		parse_champions(int argc, char *argv[]);

#endif