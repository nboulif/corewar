/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thashmap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:28:36 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/17 18:28:38 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THASHMAP_H
# define THASHMAP_H
# include "hashmap/hashmap.h"
# include "memory_manager/typemanager.h"
# include "array/array.h"
# include "btree/tbtree.h"

typedef struct			s_thmap
{
	t_hmap				hmap;
	t_typemanager		*tbnode_mng;
}						t_thmap;

int						ft_thmap_initialize(t_thmap *thmap,
	t_typemanager *tbnode_mng, t_array *array_tbtree,
	size_t (*hash)(void *s, size_t size));

void					ft_thmap_refill(t_thmap *thmap);

int						ft_thmap_remove(t_thmap *thmap, void *item);

int						ft_thmap_add(t_thmap *thmap, void *item);

#endif
