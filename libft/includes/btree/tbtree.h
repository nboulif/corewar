/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbtree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:28:36 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/17 18:28:38 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TBTREE_H
# define TBTREE_H
# include "btree/btree.h"
# include "memory_manager/typemanager.h"

/*
** named should be a pointer to a struct which respect the following :
** the first element should be of a type which differentiate it from others
** elements of the same type
*/
typedef struct			s_tbnode
{
	t_bnode				bnode;
	t_typeitem			*typeitem;
}						t_tbnode;

/*
** cmp is a custom function which make use of the first element of
** t_tbnode->named to sort the elements
*/
typedef struct			s_tbtree
{
	t_btree				btree;
	t_typemanager		*tmng;
	t_typeused			tused;
}						t_tbtree;

/*
** fill the empty btree, so it can be used
**
** @before: btree should be empty
**
** @param: btree : empty t_btree*
** @param: bnode_mmng : t_typemanager* in charge of supplying t_bnode*
**
** @return: 1 : success
** @return: 0 : memory error
** @return: -1 : param error
*/
int						ft_tbtree_initialize(t_tbtree *tbtree,
	t_typemanager *tbnode_tmng, int (*cmp)(void *s1, void *s2));

/*
** refill btree->mmng with t_bnode* stored within btree->mused
**
** @after: btree cannot be used anymore unless reconstructed
**
** @param: btree : to be destroyed t_btree*
*/
void					ft_tbtree_refill(t_tbtree *tbtree);

/*
** add item to tbtree only if item->key is not already present
**
** @param: tbtree : to be modified
** @param: item : to be added
**
** @return: 1 : success
** @return: 0 : memory error
** @return: -1 : param error
** @return: -2 : error item->key is already present
*/
int						ft_tbtree_add(t_tbtree *tbtree, void *item);

/*
** remove item from btree if item->key is already present
**
** @param: btree : to be modified
** @param: key : to be searched for (pointer to type of t_bnode->named->"first")
**
** @return: object which was removed
** @return: NULL : error
*/
void					*ft_tbtree_remove(t_tbtree *tbtree, void *key);

/*
** fill new with items from old
**
** @param: old : source
** @param: new : destination
**
** @return: 1 : success
** @return: 0 : memory error
** @return: -1 : param error
*/
int						ft_btree_fill_tcopy(t_btree *old, t_tbtree *new_tbt);

int						ft_tbtree_add_typecast(void *receiver, void *sent);

/*
** internal functions
*/
int						ft_tbtree_construct_leaves(t_tbtree *tbtree,
	t_tbnode *old_leaf);
t_tbnode				*ft_tbtree_remove_ext_tbnode(t_tbtree *tbtree,
	t_tbnode *target);
int						ft_tbtree_add_ext_tbnode(t_tbtree *tbtree,
	t_tbnode *target, void *item);

#endif
