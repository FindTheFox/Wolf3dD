/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pause.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:33:16 by bebosson          #+#    #+#             */
/*   Updated: 2020/01/31 18:55:40 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

SDL_Color			ft_hex_to_rgb(int hexa)
{
	SDL_Color color;

	color.r = hexa >> 24;
	color.g = hexa >> 16;
	color.b = hexa >> 8;
	color.a = hexa;
	return (color);
}

int					move_cursor(t_wolf *data, int *cursor)
{
	if (data->event.key.keysym.sym == SDLK_UP && *cursor > 1)
	{
		play_sound(data, data->sound.tic, 5);
		return (--*cursor);
	}
	else if (data->event.key.keysym.sym == SDLK_DOWN && *cursor < 2)
	{
		play_sound(data, data->sound.tic, 5);
		return (++*cursor);
	}
	else
		return (*cursor);
}

void				draw_cursor(t_wolf *data, int cursor)
{
	int			x;
	SDL_Rect	rect;

	x = 7;
	rect = (SDL_Rect){x * (W_WIDTH / 16), (6 + cursor)
		* (W_HEIGHT / 10), (W_WIDTH / 16) / 2, (W_HEIGHT / 10) / 2};
	set_rect_to_screen(data, &rect, 0xcc0000);
}

static void			draw_main_rect(t_wolf *data, int cursor)
{
	SDL_Texture *font;
	SDL_Rect	rect;

	font = SDL_CreateTextureFromSurface(data->renderer, data->sprite[2].img);
	SDL_RenderCopy(data->renderer, font, NULL, NULL);
	rect = (SDL_Rect){W_WIDTH / 3, W_HEIGHT / 4, 0, 0};
	data->policep = data->police;
	set_write_to_screen(data, rect, 0xcc0000ff, data->strgame);
	rect = (SDL_Rect){2 * (W_WIDTH / 16), 7 * (W_HEIGHT / 10), 2
		* (W_WIDTH / 16), 0.75 * (W_HEIGHT / 10)};
	data->policep = data->police2;
	set_write_to_screen(data, rect, 0xcc0000ff, "PLAY");
	rect = (SDL_Rect){2 * (W_WIDTH / 16), 8 * (W_HEIGHT / 10), 2
		* (W_WIDTH / 16), 0.75 * (W_HEIGHT / 10)};
	set_write_to_screen(data, rect, 0xcc0000ff, "QUIT");
	draw_cursor(data, cursor);
	SDL_RenderPresent(data->renderer);
	SDL_DestroyTexture(font);
}

void				w_pause(t_wolf *data)
{
	int	cursor;

	SDL_FlushEvent(SDL_KEYDOWN);
	SDL_FlushEvent(SDL_MOUSEMOTION);
	cursor = 1;
	draw_main_rect(data, cursor);
	play_music(data, data->sound.pausemusic);
	while (data->key[KP])
	{
		SDL_PollEvent(&data->event);
		if ((data->event.key.keysym.sym == SDLK_SPACE && cursor == 1)
		|| (data->event.key.keysym.sym == SDLK_p
		&& data->event.type == SDL_KEYDOWN))
			help_pause(data);
		else if ((data->event.key.keysym.sym == SDLK_SPACE && cursor == 2)
			|| data->event.window.event == SDL_WINDOWEVENT_CLOSE
			|| data->event.key.keysym.sym == SDLK_ESCAPE)
			clean_exit(data, NULL, 1);
		else if (data->event.key.keysym.sym == SDLK_UP
				|| data->event.key.keysym.sym == SDLK_DOWN)
		{
			cursor = move_cursor(data, &cursor);
			draw_main_rect(data, cursor);
		}
	}
}
