/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/30 20:30:51 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		depth_monster(t_object *monster)
{
	if (monster->type == 7)
		monster->depth = 1.05f;
	else if (monster->type == 8)
		monster->depth = 2.0f;
	else if (monster->type == 9)
		monster->depth = 2.0f;
}

static void		create_newmonster(t_wolf *data)
{
	int			skin;
	t_object	*newmonster;

	if (!(newmonster = (t_object *)ft_memalloc(sizeof(t_object))))
		clean_exit(data, "wolf3d: malloc error", 0);
	newmonster->x = data->monster->x;
	newmonster->y = data->monster->y;
	skin = 7;
	if (data->kill_score > 10)
		skin = 8;
	if (data->kill_score > 20)
		skin = 9;
	newmonster->type = skin;
	depth_monster(newmonster);
	newmonster->si = skin;
	newmonster->delay = newmonster->type * 10;
	newmonster->hp = get_objhp(data, newmonster);
	newmonster->hp_max = newmonster->hp;
	newmonster->sprite = data->sprite[newmonster->type];
	newmonster->speed = 0.2f + data->kill_score / 100;
	if (newmonster->speed > 0.5f)
		newmonster->speed = 0.5f;
	lst_pushback(data->monster, newmonster);
	if (data->monster == NULL)
		clean_exit(data, "wolf3d: malloc error", 0);
}

void			spawner(t_wolf *data)
{
	int	monsters;

	monsters = lst_len(data->monster) - 1;
	if (monsters < 5)
		data->monster->delay = data->monster->type * 40;
	if (monsters < 10)
		data->monster->delay = data->monster->type * 80;
	else if (monsters < 20)
		data->monster->delay = data->monster->type * 160;
	else
	{
		data->monster->delay = data->monster->type * 320;
		return ;
	}
	play_sound(data, data->sound.nmispawn, 4);
	create_newmonster(data);
}
