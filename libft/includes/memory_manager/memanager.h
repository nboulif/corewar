/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memanager.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:16:07 by dabeloos          #+#    #+#             */
/*   Updated: 2019/09/27 16:16:08 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMANAGER_H
# define MEMANAGER_H
# include <stdlib.h>
# include "array/array.h"
# include "memory_manager/typemanager.h"
# include "btree/tbtree.h"
# include "hashmap/thashmap.h"
# define MMNG_DEFAULT_SIZE_COUNT	32
# define MMNG_DEFAULT_ADDR_COUNT	2048
# define MMNG_DEFAULT_CHUNK_SIZE	262144
# define MMNG_DEFAULT_OVRLP_SIZE	1

/*
** MMNG_DEFAULT_OVRLP_SIZE
** bad implementation for hmap usage in memanager (dont use more than 1)
*/
typedef struct			s_key_sthmap
{
	size_t				key;
}						t_key_sthmap;

typedef struct			s_sthmap
{
	t_key_sthmap		size;
	t_thmap				addr_thmap;
	t_typeitem			*sthm_typeitem;
	t_typeitem			*array_typeitem;
	t_typeitem			*items_typeitem;
}						t_sthmap;

typedef struct			s_memjump
{
	struct s_memjump	*next;
	struct s_memjump	*prev;
}						t_memjump;

typedef struct			s_memanager
{
	t_typeused			sthm_used;
	t_typeused			array_used;
	t_typeused			items_used;
	t_tbtree			sthmap_tbt;
	size_t				chunk_size;
	size_t				overlap;
	t_typemanager		*sthm_mng;
	t_typemanager		*array_mng;
	t_typemanager		*items_mng;
	t_typemanager		*tbnode_mng;
	t_array				*memarrays;
}						t_memanager;

/*
** general dimensions condition
** btree condition (at least 1 address per size + 2 non-set childs)
** underflow condition -> 1st condition : see get_extended (3 jumpers)
** overflow condition
** chunk_size is too small compared to sizes & addresses
*/
int						ft_memanager_validate_amounts(size_t sizes,
	size_t addresses, size_t chunk_size, size_t overlap);

void					ft_memanager_free(t_memanager *mmng);

t_memanager				*ft_memanager_construct(size_t sizes, size_t addresses,
	size_t chunk_size, size_t overlap);

t_memanager				*ft_memanager_construct_default(void);

t_array					*ft_memanager_extend_size(
	t_memanager *mmng, size_t chunk_size);

/*
** parcourir les tailles dans le btree
** des qu'on prend a gauche on enregistre en tampon le dernier parent
** on trouve -> cours normal
** on ne trouve pas + pas de parent -> extend size (peut etre custom)
** on ne trouve pas + parent -> decoupage de pointeur + ajout du reste
** si reste <= sizeof(t_memjump) -> pas de decoupage
** dans les 3 cas : retrait de l'addresse (ou non-ajout /!\)
*/
void					*ft_memanager_get(t_memanager *mmng,
	size_t sizeof_item);

int						ft_memanager_refill(t_memanager *mmng, void *addr);

/*
** internal functions
*/
void					ft_memanager_get_as_is_refill(t_memanager *mmng,
	t_tbnode *tbnode_sthmap, t_tbtree *hash_tbt, t_tbnode *tbnode_addr);

void					*ft_memanager_get_as_is_addr(t_memanager *mmng,
	t_tbnode *tbnode_sthmap, void *addr);

t_memanager				*ft_memanager_error(t_memanager *mmng);

t_array					*ft_memanager_initialize_memarray(
	t_memanager *mmng, size_t i_memarray);

int						ft_memanager_initialize(t_memanager *mmng);

int						ft_memanager_add_addr(t_memanager *mmng,
	void *addr, size_t sizeof_addr);

#endif
