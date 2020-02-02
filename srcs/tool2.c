/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/02 20:23:33 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

float			distance(float x1, float y1, float x2, float y2)
{
	float	nb;
	float	i;
	float	threehalfs;
	t_rsqrt	conv;

	nb = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	i = nb * 0.5f;
	threehalfs = 1.5f;
	conv = (t_rsqrt){nb};
	conv.i = 0x5f3759df - (conv.i >> 1);
	conv.f *= (threehalfs - (i * conv.f * conv.f));
	return (1 / conv.f);
}

float			distance_calc(float x1, float y1, float x2, float y2)
{
	float	nb;

	nb = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
	return (nb);
}

int				get_objhp(t_wolf *data, t_object *list)
{
	int	hp;

	hp = 100000;
	if (list->type == 7)
		hp = 100;
	else if (list->type == 8)
		hp = 200;
	else if (list->type == 9)
		hp = 400;
	return (hp + data->kill_score);
}

void			put_pixel(SDL_Surface *surface, int x, int y, uint32_t color)
{
	unsigned int	*pixels;

	if (x < 0 || x >= W_WIDTH || y < 0 || y >= W_HEIGHT)
		return ;
	pixels = (unsigned int *)surface->pixels;
	pixels[x + (y * W_WIDTH)] = color;
}
