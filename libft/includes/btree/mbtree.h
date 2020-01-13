/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mbtree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:26:24 by dabeloos          #+#    #+#             */
/*   Updated: 2019/11/20 16:26:25 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MBTREE_H
# define MBTREE_H
# include "btree/btree.h"
# include "memory_manager/memanager.h"

typedef struct			s_mbtree
{
	t_btree				btree;
	t_memanager			*mmng;
}						t_mbtree;

t_mbtree				*ft_mbtree_construct(t_memanager *mmng,
	int (*cmp)(void *s1, void *s2));

int						ft_mbtree_initialize(t_mbtree *mbtree, t_memanager
	*mmng, int (*cmp)(void *s1, void *s2));

void					ft_mbtree_empty(t_mbtree *mbtree);

void					ft_mbtree_free(t_mbtree *mbtree);

int						ft_mbtree_add(t_mbtree *mbtree, void *item);

void					*ft_mbtree_remove(t_mbtree *mbtree, void *key);

int						ft_mbtree_add_typecast(void *receiver, void *sent);

int						ft_btree_fill_mcopy(t_btree *old, t_mbtree *new_mbt);

/*
** internal functions
*/
int						ft_mbtree_construct_leaves(t_mbtree *mbtree,
	t_bnode *old_leaf);
t_bnode					*ft_mbtree_remove_ext_bnode(t_mbtree *mbtree,
	t_bnode *target);
int						ft_mbtree_add_ext_bnode(t_mbtree *mbtree,
	t_bnode *target, void *item);

void					ft_mbtree_initialize_leaf(t_bnode *leaf,
	t_bnode *parent);

#endif
