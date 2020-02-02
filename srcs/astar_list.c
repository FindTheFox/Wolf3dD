/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   astar_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:47:22 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/28 18:48:52 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			alst_free(t_alst *list)
{
	t_alst	*tmp;

	while (list)
	{
		tmp = list->next;
		ft_memdel((void **)&list);
		if (tmp)
			list = tmp;
	}
}

int				alst_len(t_alst *list)
{
	int		i;
	t_alst	*tmp;

	if (list == NULL)
		return (0);
	tmp = list;
	i = 0;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	return (i);
}

void			alst_pushback(t_alst *list, t_node *node)
{
	t_alst	*head;

	if (list)
	{
		head = list;
		while (list->next)
			list = list->next;
		if (!(list->next = (t_alst *)ft_memalloc(sizeof(t_alst))))
		{
			alst_free(head);
			return ;
		}
		list->next->node = node;
		list = head;
	}
}

static void		alst_swap(t_alst *a, t_alst *b)
{
	t_node	*tmp;

	tmp = b->node;
	b->node = a->node;
	a->node = tmp;
}

void			alst_sort(t_alst *list)
{
	t_alst	*tmp;
	int		sorted;

	if (list == NULL)
		return ;
	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		tmp = list;
		while (tmp->next)
		{
			if (tmp->node->globalgoal > tmp->next->node->globalgoal)
			{
				alst_swap(tmp, tmp->next);
				sorted = 0;
			}
			tmp = tmp->next;
		}
	}
}
