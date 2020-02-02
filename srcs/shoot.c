/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/30 20:30:51 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			deal_damage_tomonster(t_wolf *data, t_object *list, int damage)
{
	if (list == NULL || list->type < 7)
		return ;
	list->hp -= damage;
	if (list->hp < 1)
	{
		++data->kill_score;
		list->dead = 1;
		list->si = 28;
		play_sound(data, data->sound.nmideath, 3);
	}
	else
	{
		list->si = list->type + 6;
		list->sprite = data->sprite[list->si];
		play_sound(data, data->sound.nmihit, 3);
	}
}

static int		hitbox(t_wolf *data)
{
	int		i;
	int		range;
	int		ms;

	ms = W_WIDTH / 2;
	if (data->monster->data.dst_fromplayer
			> data->player.wdata[data->player.weapon].range)
		return (0);
	range = ms / data->monster->data.dst_fromplayer;
	i = ms - range - 1;
	if ((data->monster->data.mid < ms + range
		&& data->monster->data.mid > ms - range))
	{
		while (++i < ms + range)
			if (data->map.depth_buffer[i]
				>= data->monster->data.dst_fromplayer)
				return (1);
	}
	return (0);
}

static void		shoot_impact(t_wolf *data)
{
	t_object	*head;

	head = data->monster;
	while (data->monster)
	{
		if (data->monster->type > 6)
			if (hitbox(data) == 1)
				deal_damage_tomonster(data, data->monster,
					data->player.wdata[data->player.weapon].damage);
		data->monster = data->monster->next;
	}
	data->monster = head;
}

static void		shoot2(t_wolf *data)
{
	if (data->player.weapon == 2)
	{
		data->player.wdata[data->player.weapon].si = 25;
		play_sound(data, data->sound.fusil, 2);
	}
	else if (data->player.weapon == 3)
	{
		data->player.wdata[data->player.weapon].si = 27;
		play_sound(data, data->sound.shotgun, 2);
	}
}

void			shoot(t_wolf *data)
{
	if (data->key[ML] && data->fire_delay < 1)
	{
		if (data->player.weapon == 0)
		{
			data->player.wdata[data->player.weapon].si = 21;
			play_sound(data, data->sound.hand, 2);
		}
		else if (data->player.weapon == 1)
		{
			data->player.wdata[data->player.weapon].si = 23;
			play_sound(data, data->sound.gun, 2);
		}
		else if (data->player.weapon == 2 || data->player.weapon == 3)
			shoot2(data);
		shoot_impact(data);
		data->fire_delay = data->player.wdata[data->player.weapon].delay;
		data->skin_delay = 7;
	}
}
