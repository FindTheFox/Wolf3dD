/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 16:07:10 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/02 20:41:50 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			help_pause(t_wolf *data)
{
	data->key[KP] = 0;
	play_sound(data, data->sound.playerspawn, 1);
	play_music(data, data->sound.ingmusic);
}

uint32_t		get_pixel(t_wolf *data, int si, float samplex, float sampley)
{
	int				sx;
	int				sy;
	uint8_t			*p;
	t_sprite		surface;

	surface = data->sprite[si];
	sx = samplex * surface.img->w;
	sy = sampley * surface.img->h;
	p = (uint8_t *)surface.img->pixels + sy * surface.img->pitch
		+ sx * surface.img->format->BytesPerPixel;
	return (p[2] | p[1] << 8 | p[0] << 16 | 255 << 24);
}

uint32_t		get_pixel_obj(t_object *l, int tx, int ty)
{
	uint8_t			*p;
	t_sprite		surface;

	surface = l->sprite;
	p = (uint8_t *)surface.img->pixels + ty * surface.img->pitch
		+ tx * surface.img->format->BytesPerPixel;
	return (p[2] | p[1] << 8 | p[0] << 16 | 255 << 24);
}

uint32_t		get_pixel_floor(t_wolf *data, int si, float x, float y)
{
	int				sx;
	int				sy;
	uint8_t			*p;
	t_sprite		surface;
	uint32_t		pixel;

	surface = data->sprite[si];
	sx = x;
	sy = y;
	p = (uint8_t *)surface.img->pixels + sy * surface.img->pitch
		+ sx * surface.img->format->BytesPerPixel;
	pixel = (p[2] | p[1] << 8 | p[0] << 16 | 255 << 24);
	return (fog(data, pixel, data->ray.distcurrent));
}

SDL_Surface		*new_surface(int w, int h)
{
	Uint32	color[4];

	color[0] = 0x000000ff;
	color[1] = 0x0000ff00;
	color[2] = 0x00ff0000;
	color[3] = 0xff000000;
	return (SDL_CreateRGBSurface(0, w, h, 32,
				color[0], color[1], color[2], color[3]));
}
