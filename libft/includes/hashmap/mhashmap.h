/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mhashmap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 20:27:08 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 20:27:10 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MHASHMAP_H
# define MHASHMAP_H
# include "hashmap/hashmap.h"
# include "memory_manager/memanager.h"
# include "array/marray.h"
# include "btree/mbtree.h"

typedef struct			s_mhmap
{
	t_hmap				hmap;
	t_memanager			*mmng;
}						t_mhmap;

int						ft_mhmap_initialize(t_mhmap *mhmap, t_memanager *mmng,
	size_t size, size_t (*hash)(void *s, size_t size));

t_mhmap					*ft_mhmap_construct(t_memanager *mmng, size_t size,
	size_t (*hash)(void *s, size_t size));

void					ft_mhmap_empty(t_mhmap *mhmap);

void					ft_mhmap_free(t_mhmap *mhmap);

int						ft_mhmap_add(t_mhmap *mhmap, void *item);

int						ft_mhmap_remove(t_mhmap *mhmap, void *item);

int						ft_hmap_fill_marray(t_hmap *hmap, t_marray *marray);

#endif
