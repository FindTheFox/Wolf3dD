/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 20:30:08 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/02 20:19:47 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			ft_remove_light(Uint8 *component, double delta, int arg)
{
	if (*component > 0)
		*component = (*component * (1 - delta) + ((0x0 >> arg) * delta));
}

Uint32			light_shade(Uint32 hexa, float distance)
{
	SDL_Color	color;
	double		delta;

	delta = distance / 10;
	delta > 0.9 ? delta = 0.9 : 0;
	delta /= 1.50;
	hexa |= 0xFF000000;
	color = (SDL_Color){hexa >> 24, hexa >> 16, hexa >> 8, hexa};
	ft_remove_light(&color.r, delta, 24);
	ft_remove_light(&color.g, delta, 16);
	ft_remove_light(&color.b, delta, 8);
	ft_remove_light(&color.a, delta, 0);
	return ((color.r << 24) + (color.g << 16) + (color.b << 8) + (color.a));
}

int				white_fog(t_wolf *d, Uint32 hexa, float distance)
{
	float intensity;

	d->rgb = fill_rgb(hexa);
	intensity = d->obj_intens / distance * 8;
	if (intensity < 1)
	{
		d->rgb.r *= intensity;
		d->rgb.g *= intensity;
		d->rgb.b *= intensity;
	}
	return (rgb_to_hsv(d->rgb.r, d->rgb.g, d->rgb.b));
}

int				fog(t_wolf *d, Uint32 hexa, float distance)
{
	float		intensity;
	SDL_Color	c;

	if (d->fog == 1)
	{
		c = (SDL_Color){hexa >> 24, hexa >> 16, hexa >> 8, hexa};
		intensity = d->obj_intens / distance * 1.5;
		if (intensity < 1)
		{
			c.r *= intensity;
			c.g *= intensity;
			c.b *= intensity;
			c.a *= intensity;
			return ((c.r << 24) + (c.g << 16) + (c.b << 8) + (c.a));
		}
	}
	else if (d->fog == 2)
		return (white_fog(d, hexa, distance));
	else if (d->fog == 3)
		return (light_shade(hexa, distance));
	return (hexa);
}
