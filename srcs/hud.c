/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 15:35:06 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/16 19:31:48 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		health_color(t_wolf *data, int ratio)
{
	if (data->player.health > 0)
		SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 100);
	if (data->player.health > ratio * 20)
		SDL_SetRenderDrawColor(data->renderer, 255, 165, 0, 100);
	if (data->player.health > ratio * 40)
		SDL_SetRenderDrawColor(data->renderer, 255, 255, 0, 100);
	if (data->player.health > ratio * 60)
		SDL_SetRenderDrawColor(data->renderer, 50, 200, 35, 0);
	if (data->player.health > ratio * 80)
		SDL_SetRenderDrawColor(data->renderer, 30, 150, 0, 100);
}

void			health(t_wolf *data)
{
	int			p;
	int			ratio;
	SDL_Rect	rect;

	ratio = data->player.health_max / 100;
	SDL_SetRenderDrawColor(data->renderer, 0, 0, 0, 100);
	rect.x = 10;
	rect.y = W_HEIGHT / 8 * 7;
	rect.h = W_HEIGHT / 10;
	rect.w = W_WIDTH / 4;
	SDL_RenderFillRect(data->renderer, &rect);
	p = 2;
	rect.x = 10 + p;
	rect.y = W_HEIGHT / 8 * 7 + p;
	rect.h = W_HEIGHT / 10 - p * 2;
	rect.w = ((W_WIDTH / 4) / 100) * (data->player.health / ratio) - p * 2;
	health_color(data, ratio);
	SDL_RenderFillRect(data->renderer, &rect);
}

void			cursor(t_wolf *data)
{
	SDL_SetRenderDrawColor(data->renderer, 255, 0, 0, 100);
	SDL_RenderDrawLine(data->renderer,
			W_WIDTH / 2 - 15, W_HEIGHT / 2,
			W_WIDTH / 2 + 15, W_HEIGHT / 2);
	SDL_RenderDrawLine(data->renderer,
			W_WIDTH / 2, W_HEIGHT / 2 - 15,
			W_WIDTH / 2, W_HEIGHT / 2 + 15);
	SDL_RenderDrawLine(data->renderer,
			W_WIDTH / 2 - 15, W_HEIGHT / 2 - 1,
			W_WIDTH / 2 + 15, W_HEIGHT / 2 - 1);
	SDL_RenderDrawLine(data->renderer,
			W_WIDTH / 2 - 1, W_HEIGHT / 2 - 15,
			W_WIDTH / 2 - 1, W_HEIGHT / 2 + 15);
	SDL_RenderDrawLine(data->renderer,
			W_WIDTH / 2 - 15, W_HEIGHT / 2 + 1,
			W_WIDTH / 2 + 15, W_HEIGHT / 2 + 1);
	SDL_RenderDrawLine(data->renderer,
			W_WIDTH / 2 + 1, W_HEIGHT / 2 - 15,
			W_WIDTH / 2 + 1, W_HEIGHT / 2 + 15);
}
