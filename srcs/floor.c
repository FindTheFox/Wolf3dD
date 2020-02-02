/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 17:26:54 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/31 20:50:17 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int		checktexture(t_wolf *d)
{
	int t;
	int c;

	c = 0;
	t = 0;
	if (d->floorstyle == 0)
		t = 1;
	else
	{
		if (d->floorstyle == 2)
			c = ((int)(d->ray.currentfloorx + d->ray.currentfloory)) % 2;
		else
			c = ((int)d->ray.currentfloorx + (int)d->ray.currentfloory) % 2;
		if (c == 0)
			t = 0;
		else
			t = 1;
	}
	return (t);
}

static void		pxl_add(t_wolf *d, int y, int x, int tx)
{
	int tex;

	if (tx == 1)
		tex = 0;
	else
		tex = checktexture(d);
	d->ray.wtx = (int)(d->ray.currentfloorx * d->sprite[tex].img->w)
		% d->sprite[tex].img->w;
	d->ray.wty = (int)(d->ray.currentfloory * d->sprite[tex].img->h)
		% d->sprite[tex].img->h;
	put_pixel(d->screen, x, y, get_pixel_floor(d, tex, d->ray.wtx, d->ray.wty));
}

static void		floor_calcul(t_wolf *d, int x)
{
	int y;

	d->ray.distwall = d->ray.perpwalldist;
	if (d->ray.wallbot < 0)
		d->ray.wallbot = W_HEIGHT;
	y = d->ray.wallbot - 1;
	while (++y <= W_HEIGHT)
	{
		d->ray.distcurrent = W_HEIGHT / (2.0 * y - W_HEIGHT);
		d->ray.weight = d->ray.distcurrent / d->ray.distwall;
		d->ray.currentfloorx = d->ray.weight * d->ray.floorwallx
			+ (1.0 - d->ray.weight) * d->player.x;
		d->ray.currentfloory = d->ray.weight * d->ray.floorwally
			+ (1.0 - d->ray.weight) * d->player.y;
		pxl_add(d, y, x, 0);
		pxl_add(d, W_HEIGHT - y, x, 1);
	}
}

void			draw_floor_ceilling(t_wolf *d, int x)
{
	if (d->ray.wallside == 0)
	{
		d->ray.floorwallx = d->ray.maposx;
		d->ray.floorwally = d->ray.maposy + d->ray.wallx;
		if (d->ray.dirx < 0)
			d->ray.floorwallx += 1.0;
	}
	else
	{
		d->ray.floorwallx = d->ray.maposx + d->ray.wallx;
		d->ray.floorwally = d->ray.maposy;
		if (d->ray.diry < 0)
			d->ray.floorwally += 1.0;
	}
	floor_calcul(d, x);
}
