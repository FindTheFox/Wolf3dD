/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:30:19 by bebosson          #+#    #+#             */
/*   Updated: 2020/01/16 19:32:55 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void	set_write_to_screen(t_wolf *data, SDL_Rect rect, int c, char *str)
{
	data->surf_write = TTF_RenderText_Solid(data->policep, str,
		ft_hex_to_rgb(c));
	data->text_write = SDL_CreateTextureFromSurface(data->renderer,
		data->surf_write);
	SDL_QueryTexture(data->text_write, 0, 0, &(rect.w), &(rect.h));
	SDL_RenderCopy(data->renderer, data->text_write, NULL, &rect);
	SDL_FreeSurface(data->surf_write);
	SDL_DestroyTexture(data->text_write);
}

void	set_rect_to_screen(t_wolf *data, SDL_Rect *rect, int c)
{
	int a;

	a = 0xff;
	SDL_SetRenderDrawColor(data->renderer, c >> 16 & a, c >> 8 & a, c & a, 100);
	SDL_RenderFillRect(data->renderer, rect);
}

void	add_sc_x(t_wolf *data)
{
	if (data->event.key.keysym.sym == SDLK_b)
	{
		data->key[KB] = data->event.type == SDL_KEYDOWN ? 1 : 0;
		if (data->key[KB] == 1 && data->map.sc_x < 5)
			data->map.sc_x++;
	}
	else if (data->event.key.keysym.sym == SDLK_n)
	{
		data->key[KN] = data->event.type == SDL_KEYDOWN ? 1 : 0;
		if (data->key[KN] == 1 && data->map.sc_x > 2)
			data->map.sc_x--;
	}
}
