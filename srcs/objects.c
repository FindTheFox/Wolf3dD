/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/31 18:36:00 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void				get_obj_calc2(t_object *l)
{
	l->data.spriteheight = abs((int)(W_HEIGHT / (l->data.transformy)));
	l->data.drawstarty = -l->data.spriteheight / 2 + W_HEIGHT / 2;
	if (l->data.drawstarty < 0)
		l->data.drawstarty = 0;
	l->data.drawendy = l->data.spriteheight / 2 + W_HEIGHT / 2;
	if (l->data.drawendy >= W_HEIGHT)
		l->data.drawendy = W_HEIGHT - 1;
	l->data.spritewidth = abs((int)(W_HEIGHT / l->data.transformy));
	l->data.drawstartx = -l->data.spritewidth / 2 + l->data.spritescreenx;
	if (l->data.drawstartx < 0)
		l->data.drawstartx = 0;
	l->data.drawendx = l->data.spritewidth / 2 + l->data.spritescreenx;
	if (l->data.drawendx >= W_WIDTH)
		l->data.drawendx = W_WIDTH - 1;
	l->data.mid = (l->data.drawstartx / 2) + (l->data.drawendx / 2);
}

static void				get_obj_calc(t_wolf *d, t_object *l)
{
	float	spritex;
	float	spritey;

	l->data.dst_fromplayer = distance_calc(d->player.x, d->player.y,
		l->x, l->y);
	spritex = l->x - d->player.x;
	spritey = l->y - d->player.y;
	l->data.invdet = 1.0 / (d->player.planex * d->player.diry
		- d->player.dirx * d->player.planey);
	l->data.transformx = l->data.invdet * (d->player.diry * spritex
		- d->player.dirx * spritey);
	l->data.transformy = l->data.invdet * (-d->player.planey * spritex
		+ d->player.planex * spritey);
	l->data.spritescreenx = (int)((W_WIDTH / 2) * (1 + l->data.transformx
		/ l->data.transformy));
	get_obj_calc2(l);
}

static void				help_display(t_wolf *d, t_object *l, int sx, int sy)
{
	uint32_t	pixel;
	int			p;

	p = (sy) * 256 - W_HEIGHT * 128 + l->data.spriteheight * 128;
	d->ray.wty = ((p * l->sprite.img->h) / l->data.spriteheight) / 256;
	pixel = get_pixel_obj(l, d->ray.wtx, d->ray.wty);
	if (pixel != l->data.zpixel)
		put_pixel(d->screen, sx, sy, fog(d, pixel, l->data.dst_fromplayer));
	l->data.dst_fromplayer = distance(d->player.x, d->player.y,
		l->x, l->y);
}

static void				display_object(t_wolf *d, t_object *l)
{
	int			sx;
	int			sy;

	sx = l->data.drawstartx;
	while (sx < l->data.drawendx)
	{
		d->ray.wtx = (int)(256 * (sx - (-((int)l->data.spritewidth) / 2
			+ l->data.spritescreenx))
				* l->sprite.img->w / l->data.spritewidth) / 256;
		if (l->data.transformy > 0 && sx > 0 && sx < W_WIDTH
		&& l->data.transformy < d->map.depth_buffer[sx])
		{
			sy = l->data.drawstarty;
			while (sy < l->data.drawendy)
			{
				help_display(d, l, sx, sy);
				d->map.depth_buffer[sx] = l->data.dst_fromplayer;
				sy++;
			}
		}
		sx++;
	}
}

void					objects(t_wolf *data, t_object *list)
{
	t_object	*head;

	head = list;
	if (list == NULL)
		return ;
	while (list)
	{
		list->data.zpixel = get_pixel(data, list->si, 0, 0);
		if ((list->type > 2 && list->type < 10) || list->type == 28)
		{
			list->i = (int)list->x + data->map.width * (int)list->y;
			get_obj_calc(data, list);
			display_object(data, list);
		}
		list = list->next;
	}
	list = head;
}
