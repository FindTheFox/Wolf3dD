/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:48:08 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/02 20:21:19 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			game_over(t_wolf *data)
{
	play_sound(data, data->sound.playerdeath, 5);
	end_screen(data, "GAME OVER");
}

void			set_end_pt(t_wolf *d, int i)
{
	d->end.y = i / d->map.width;
	d->end.x = i - (d->end.y * d->map.width) + 1;
}

void			end_screen_rect(t_wolf *d, char *str)
{
	SDL_Rect	rect;
	SDL_Texture	*font;

	font = SDL_CreateTextureFromSurface(d->renderer, d->sprite[2].img);
	SDL_RenderCopy(d->renderer, font, NULL, NULL);
	rect = (SDL_Rect){W_WIDTH / 3, W_HEIGHT / 4, 0, 0};
	d->policep = d->police;
	set_write_to_screen(d, rect, 0xcc0000ff, d->strgame);
	rect = (SDL_Rect){W_WIDTH / 2, W_HEIGHT / 5, 0, 0};
	d->policep = d->police2;
	set_write_to_screen(d, rect, 0xcc0000ff, str);
	rect = (SDL_Rect){2 * (W_WIDTH / 16), 8 * (W_HEIGHT / 10), 2
		* (W_WIDTH / 16), 0.75 * (W_HEIGHT / 10)};
	d->policep = d->police2;
	set_write_to_screen(d, rect, 0xcc0000ff, "Press [SPACE] for quit");
	SDL_RenderPresent(d->renderer);
	SDL_DestroyTexture(font);
}

void			end_screen(t_wolf *data, char *str)
{
	int flag;

	flag = 1;
	SDL_FlushEvent(SDL_KEYDOWN);
	SDL_FlushEvent(SDL_MOUSEMOTION);
	end_screen_rect(data, str);
	while (flag)
	{
		SDL_PollEvent(&data->event);
		if ((data->event.key.keysym.sym == SDLK_SPACE)
			|| data->event.window.event == SDL_WINDOWEVENT_CLOSE
			|| data->event.key.keysym.sym == SDLK_ESCAPE)
		{
			clean_exit(data, NULL, 1);
			flag = 0;
		}
	}
}
