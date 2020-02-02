/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 14:46:06 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/31 20:51:33 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		perp_height(t_wolf *d)
{
	if (d->ray.wallside == 0)
		d->ray.perpwalldist = fabs((d->ray.maposx - d->player.x
				+ (1 - d->ray.stepx) / 2) / d->ray.dirx);
	else
		d->ray.perpwalldist = fabs((d->ray.maposy - d->player.y
				+ (1 - d->ray.stepy) / 2) / d->ray.diry);
	d->ray.height = (int)(W_HEIGHT / d->ray.perpwalldist);
	d->ray.walltop = (int)-d->ray.height / 2 + W_HEIGHT / 2;
	if (d->ray.walltop < 0)
		d->ray.walltop = 0;
	d->ray.wallbot = (int)d->ray.height / 2 + W_HEIGHT / 2;
	if (d->ray.wallbot > W_HEIGHT)
		d->ray.wallbot = W_HEIGHT - 1;
}

static void		hitwall(t_wolf *data)
{
	data->ray.wallhit = 0;
	while (data->ray.wallhit == 0)
	{
		if (data->ray.sidedistx < data->ray.sidedisty)
		{
			data->ray.sidedistx += data->ray.deltadistx;
			data->ray.maposx += data->ray.stepx;
			data->ray.wallside = 0;
		}
		else
		{
			data->ray.sidedisty += data->ray.deltadisty;
			data->ray.maposy += data->ray.stepy;
			data->ray.wallside = 1;
		}
		if (data->map.map[data->ray.maposy * data->map.width
				+ data->ray.maposx] == 1)
			data->ray.wallhit = 1;
	}
	perp_height(data);
}

static void		get_side(t_wolf *data)
{
	if (data->ray.dirx < 0)
	{
		data->ray.sidedistx = (data->player.x - data->ray.maposx)
			* data->ray.deltadistx;
		data->ray.stepx = -1;
	}
	else
	{
		data->ray.sidedistx = (data->ray.maposx + 1.0 - data->player.x)
			* data->ray.deltadistx;
		data->ray.stepx = 1;
	}
	if (data->ray.diry < 0)
	{
		data->ray.sidedisty = (data->player.y - data->ray.maposy)
			* data->ray.deltadisty;
		data->ray.stepy = -1;
	}
	else
	{
		data->ray.sidedisty = (data->ray.maposy + 1.0 - data->player.y)
			* data->ray.deltadisty;
		data->ray.stepy = 1;
	}
}

static void		ray_calcul(t_wolf *data, int x)
{
	data->ray.camera = 2 * x / (double)W_WIDTH - 1;
	data->ray.dirx = data->player.dirx + data->player.planex * data->ray.camera;
	data->ray.diry = data->player.diry + data->player.planey * data->ray.camera;
	data->ray.deltadistx = sqrt(1 + (data->ray.diry * data->ray.diry)
			/ (data->ray.dirx * data->ray.dirx));
	data->ray.deltadisty = sqrt(1 + (data->ray.dirx * data->ray.dirx)
			/ (data->ray.diry * data->ray.diry));
	data->ray.maposx = (int)data->player.x;
	data->ray.maposy = (int)data->player.y;
	get_side(data);
}

void			raycasting(t_wolf *data)
{
	int x;

	x = -1;
	while (++x < W_WIDTH)
	{
		ray_calcul(data, x);
		hitwall(data);
		get_tex(data);
		draw_wall(data, x);
		draw_floor_ceilling(data, x);
	}
}
