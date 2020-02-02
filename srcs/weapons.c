/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/28 18:52:31 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		center_weapon(t_wolf *data, int i)
{
	if (data->player.weapon == 0)
		data->player.wdata[i].column = (data->player.wdata[i].height / 2 - 35);
	else
		data->player.wdata[i].column = 0;
}

static void		get_weapondata(t_wolf *data)
{
	int			i;
	int			si;
	SDL_Surface	*weapon;

	i = data->player.weapon;
	si = data->player.wdata[i].si;
	weapon = data->sprite[si].img;
	data->player.wdata[i].zpixel = get_pixel(data, si, 0, 0);
	data->player.wdata[i].height = W_HEIGHT / 3;
	data->player.wdata[i].ratio = (float)weapon->h / (float)weapon->w;
	data->player.wdata[i].width = data->player.wdata[i].height
		/ data->player.wdata[i].ratio;
	center_weapon(data, i);
}

static void		update_weaponskin(t_wolf *data)
{
	--data->fire_delay;
	if (--data->skin_delay > 0)
		return ;
	if (data->player.weapon == 0)
		data->player.wdata[data->player.weapon].si = 20;
	else if (data->player.weapon == 1)
		data->player.wdata[data->player.weapon].si = 22;
	else if (data->player.weapon == 2)
		data->player.wdata[data->player.weapon].si = 24;
	else if (data->player.weapon == 3)
		data->player.wdata[data->player.weapon].si = 26;
}

void			weapons(t_wolf *data)
{
	int			i;
	int			x;
	int			y;
	uint32_t	pixel;

	i = data->player.weapon;
	get_weapondata(data);
	x = -1;
	while (++x < data->player.wdata[i].width)
	{
		y = -1;
		while (++y < data->player.wdata[i].height)
		{
			pixel = get_pixel(data, data->player.wdata[i].si,
					x / data->player.wdata[i].width,
					y / data->player.wdata[i].height);
			if (pixel == data->player.wdata[i].zpixel)
				continue ;
			put_pixel(data->screen,
					(W_WIDTH / 2) - data->player.wdata[i].column + x,
					(W_HEIGHT - data->player.wdata[i].height) + y, pixel);
		}
	}
	update_weaponskin(data);
}
