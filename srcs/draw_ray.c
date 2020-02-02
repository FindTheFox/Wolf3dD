/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 01:04:10 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/02 20:20:10 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

uint32_t		get_pixel_ray(t_wolf *data, int si, float x, float y)
{
	uint8_t			*p;
	t_sprite		surface;
	Uint32			pixel;

	surface = data->sprite[si];
	p = (uint8_t *)surface.img->pixels + (int)y * surface.img->pitch
		+ (int)x * surface.img->format->BytesPerPixel;
	pixel = (p[2] | p[1] << 8 | p[0] << 16 | 255 << 24);
	return (fog(data, pixel, data->ray.perpwalldist));
}

void			draw_wall(t_wolf *d, int x)
{
	int y;
	int dis;

	if (d->ray.wallside == 0)
		d->ray.wallx = d->player.y + d->ray.perpwalldist * d->ray.diry;
	else
		d->ray.wallx = d->player.x + d->ray.perpwalldist * d->ray.dirx;
	d->map.depth_buffer[x] = d->ray.perpwalldist;
	d->ray.wallx = d->ray.wallx - (int)d->ray.wallx;
	d->ray.wtx = (int)(d->ray.wallx * (double)d->sprite[d->ray.tex].img->w);
	if ((d->ray.wallside == 0 && d->ray.dirx > 0)
			|| (d->ray.wallside == 1 && d->ray.diry < 0))
		d->ray.wtx = d->sprite[d->ray.tex].img->w - d->ray.wtx;
	y = d->ray.walltop;
	while (y < d->ray.wallbot)
	{
		dis = y * 256 - W_HEIGHT * 128 + d->ray.height * 128;
		d->ray.wty = ((dis * d->sprite[d->ray.tex].img->h)
				/ d->ray.height) / 256;
		put_pixel(d->screen, x, y,
			get_pixel_ray(d, d->ray.tex, d->ray.wtx, d->ray.wty));
		y++;
	}
}

void			get_tex(t_wolf *d)
{
	if (!(d->ray.wallside) && d->ray.dirx < 0)
		d->ray.tex = 16;
	else if (!(d->ray.wallside) && d->ray.dirx >= 0)
		d->ray.tex = 17;
	else if (d->ray.wallside && d->ray.diry < 0)
		d->ray.tex = 18;
	else if (d->ray.wallside && d->ray.diry >= 0)
		d->ray.tex = 19;
}
