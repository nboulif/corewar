/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dabeloos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:28:36 by dabeloos          #+#    #+#             */
/*   Updated: 2019/06/17 18:28:38 by dabeloos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H
# include "array/array.h"
# include "basic_functions/basicft.h"

typedef struct			s_bnode
{
	void				*named;
	struct s_bnode		*left;
	struct s_bnode		*right;
	struct s_bnode		*up;
	int					rank;
}						t_bnode;

typedef struct			s_btree
{
	t_bnode				*root;
	int					(*cmp)(void *s1, void *s2);
}						t_btree;

/*
** get object which has key
**
** @param: btree : to search in
** @param: key : to be searched for (pointer to type of t_bnode->named->"first")
**
** @return: objet which has key
** @return: NULL : btree does not contain key
*/
void					*ft_btree_get(t_btree *btree, void *key);

/*
** check if btree contains key
**
** @param: btree : to search in
** @param: key : to be searched for (pointer to type of t_bnode->named->"first")
**
** @return: 1 : btree does contain key
** @return: 0 : btree does not contain key
*/
int						ft_btree_contains(t_btree *btree, void *key);

/*
** replace item from btree only if item->key is already present
**
** @param: btree : to be modified
** @param: item : to be added
**
** @return: object which was removed
** @return: NULL : error
*/
void					*ft_btree_replace(t_btree *btree, void *item);

/*
** apply f on each node starting from sent in sorted order, using receiver
** as the appliation tool
**
** @param: receiver : tool used in the process of f
** @param: sent : the current element from a t_btree*
** @param: f : the application function
**
** @return: 1 : success
** @return: 0 : memory error
** @return: -1 : error
*/
int						ft_btree_bnode_iteration(void *receiver, t_bnode *sent,
	int (*f)(void *receiver, void *sent));

/*
** fill array with items from btree
**
** @param: btree : source
** @param: new : destination
**
** @return: 1 : success
** @return: 0 : memory error
** @return: -1 : param error
*/
int						ft_btree_is_empty(t_btree *btree);

int						ft_btree_fill_array(t_btree *btree, t_array *array);

int						ft_btree_cmp_ascii(void *s1, void *s2);
int						ft_btree_cmp_size(void *s1, void *s2);
int						ft_btree_cmp_addr(void *s1, void *s2);

/*
** internal functions
*/
t_bnode					*ft_btree_get_bnode(t_btree *btree, void *key);
t_bnode					*ft_btree_get_min_bnode(t_bnode *bnode);
t_bnode					*ft_btree_get_min_equal_or_greater_bnode(t_btree *btree,
	void *key);
t_bnode					**ft_btree_bnode_referent(t_btree *btree,
	t_bnode *bnode);
int						ft_bnode_sibling_spin(t_bnode *child,
	t_bnode **sibling);
void					ft_btree_rotate(t_btree *btree, t_bnode *bn, int spin);
int						ft_bnode_has_two_leaves(t_bnode *bnode);

void					ft_btree_rebalance_added(t_btree *btree, t_bnode *bn);
void					ft_btree_rebalance_deleted(t_btree *btree, t_bnode *bn);

#endif
