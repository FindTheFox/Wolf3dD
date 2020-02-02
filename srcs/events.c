/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/30 20:10:59 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		moves_events(t_wolf *data)
{
	if (data->event.key.keysym.sym == SDLK_q)
		data->key[KQ] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_e)
		data->key[KE] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_w
		|| data->event.key.keysym.sym == SDLK_UP)
		data->key[KW] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_a
		|| data->event.key.keysym.sym == SDLK_LEFT)
		data->key[KA] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_s
		|| data->event.key.keysym.sym == SDLK_DOWN)
		data->key[KS] = data->event.type == SDL_KEYDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_d
		|| data->event.key.keysym.sym == SDLK_RIGHT)
		data->key[KD] = data->event.type == SDL_KEYDOWN ? 1 : 0;
}

static void		get_events(t_wolf *data)
{
	moves_events(data);
	if (data->event.button.button == SDL_BUTTON_LEFT)
		data->key[ML] = data->event.type == SDL_MOUSEBUTTONDOWN ? 1 : 0;
	else if (data->event.button.button == SDL_BUTTON_RIGHT)
		data->key[MR] = data->event.type == SDL_MOUSEBUTTONDOWN ? 1 : 0;
	else if (data->event.key.keysym.sym == SDLK_m)
	{
		if (data->event.type == SDL_KEYDOWN)
			data->key[KM] = data->key[KM] ? 0 : 1;
	}
	else if (data->event.key.keysym.sym == SDLK_p)
	{
		if (data->event.type == SDL_KEYDOWN)
			data->key[KP] = data->key[KP] ? 0 : 1;
	}
	else if (data->event.key.keysym.sym == SDLK_y
		&& data->event.type == SDL_KEYDOWN)
		switch_floor(data);
	else if (data->event.key.keysym.sym == SDLK_f
		&& data->event.type == SDL_KEYDOWN)
		switch_fog(data);
}

void			events(t_wolf *data)
{
	while (SDL_PollEvent(&data->event))
	{
		if ((data->event.key.keysym.sym == SDLK_ESCAPE
		&& data->event.type == SDL_KEYDOWN)
		|| data->event.type == SDL_QUIT)
			clean_exit(data, NULL, 1);
		else if (data->event.key.keysym.sym == SDLK_b
		|| data->event.key.keysym.sym == SDLK_n)
			add_sc_x(data);
		else if (data->key[KP])
			w_pause(data);
		else if (data->event.key.keysym.sym == SDLK_t
		&& data->event.type == SDL_KEYDOWN)
			switch_texture(data);
		else if (data->event.key.keysym.sym == SDLK_LSHIFT)
			data->key[SHIFT] = data->event.type == SDL_KEYDOWN ? 1 : 0;
		else if (data->event.type == SDL_MOUSEMOTION)
			data->key[MOUSE] = 1;
		else
			get_events(data);
	}
	movements(data);
}
