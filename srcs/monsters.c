/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monsters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/30 20:52:25 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			remove_deadmobs(t_wolf *data)
{
	t_object	*tmp;
	t_object	*head;

	head = data->monster;
	while (data->monster && data->monster->dead == 1)
	{
		data->pfdata.list[data->monster->i].bobstacle = 0;
		tmp = data->monster->next;
		ft_memdel((void **)&data->monster);
		data->monster = tmp;
		head = data->monster;
	}
	while (data->monster)
	{
		tmp = data->monster;
		data->monster = data->monster->next;
		while (data->monster && data->monster->dead == 1)
		{
			data->pfdata.list[data->monster->i].bobstacle = 0;
			tmp->next = data->monster->next;
			ft_memdel((void **)&data->monster);
			data->monster = tmp->next;
		}
	}
	data->monster = head;
}

static void		smoothness(t_wolf *data, t_node *current)
{
	float	tmpx;
	float	tmpy;

	tmpx = (current->x + 0.5f - data->monster->x) * data->monster->speed;
	tmpy = (current->y + 0.5f - data->monster->y) * data->monster->speed;
	data->monster->x += tmpx;
	data->monster->y += tmpy;
	if (data->monster->x < 0
		|| data->monster->x > data->map.width
		|| data->monster->y < 0
		|| data->monster->y > data->map.height
		|| data->map.map[(int)data->monster->x
			+ data->map.width * (int)data->monster->y] == 1)
	{
		data->monster->x -= tmpx;
		data->monster->y -= tmpy;
	}
}

static void		monster_moves(t_wolf *data)
{
	t_node	*current;

	astar(data);
	current = data->pfdata.end;
	if (current == NULL)
		return ;
	while (current->parent)
	{
		if (current->parent == data->pfdata.start)
			break ;
		current = current->parent;
	}
	smoothness(data, current);
	data->monster->delay = data->monster->type + 10;
}

static void		monster_actions(t_wolf *data)
{
	float	dst;

	if (data->monster->dead == 1)
		return ;
	data->pfdata.start = &data->pfdata.list[data->monster->i];
	data->pfdata.end = &data->pfdata.list[data->player.pos];
	dst = distance(data->monster->x, data->monster->y,
			data->pfdata.end->x, data->pfdata.end->y);
	if (dst > data->monster->depth)
	{
		data->monster->si = data->monster->type;
		data->monster->sprite = data->sprite[data->monster->si];
		if (dst < 12.5f || data->monster->hp < data->monster->hp_max)
			monster_moves(data);
	}
	else
	{
		play_sound(data, data->sound.nmiatk, 4);
		data->monster->si = data->monster->type + 3;
		data->monster->sprite = data->sprite[data->monster->si];
		data->player.health -= data->monster->type * 2;
		data->monster->delay = data->monster->type * 10;
		if (data->player.health < 1)
			game_over(data);
	}
}

void			monsters(t_wolf *data)
{
	t_object	*head;

	head = data->monster;
	while (data->monster)
	{
		data->monster->i = (int)data->monster->x
			+ data->map.width * (int)data->monster->y;
		if (data->monster->type > 5 && data->monster->type < 10)
			if (--data->monster->delay < 1)
			{
				if (data->monster->type == 6)
					spawner(data);
				else
					monster_actions(data);
			}
		data->monster = data->monster->next;
	}
	data->monster = head;
	remove_deadmobs(data);
}
