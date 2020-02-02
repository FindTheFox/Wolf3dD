/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/31 19:15:14 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		init_sdl(t_wolf *data)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
		clean_exit(data, "wolf3d: SDL_Init fail", 0);
	data->sdl_on = 1;
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
		clean_exit(data, "wolf3d: error Mix_OpenAudio", 0);
	else
		audio_init(data);
	if (TTF_Init() == -1)
		clean_exit(data, "wolf3d: error TTF_init", 0);
	data->pwindow = SDL_CreateWindow("saneveu wolf3d",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			W_WIDTH, W_HEIGHT, 0);
	if (!(data->police = TTF_OpenFont("img/police/AmazDooMLeft.ttf", 200)))
		clean_exit(data, "wolf3d: error TTF_OpenFont", 0);
	if (!(data->police2 = TTF_OpenFont("img/police/bit.ttf", 20)))
		clean_exit(data, "wolf3d: error TTF_OpenFont", 0);
	if (!(data->police3 = TTF_OpenFont("img/police/bit.ttf", 8)))
		clean_exit(data, "wolf3d: error TTF_OpenFont", 0);
}

static void		launch_game(t_wolf *data)
{
	init_sdl(data);
	if (data->pwindow)
	{
		if (!(data->renderer = SDL_CreateRenderer(data->pwindow, -1,
			SDL_RENDERER_ACCELERATED)))
			clean_exit(data, "wolf3d: SDL_CreateRenderer fail", 0);
		load_datagame(data);
		while (1)
		{
			display(data);
			events(data);
		}
	}
	else
		clean_exit(data, "wolf3d: SDL_CreateWindow fail", 0);
}

void			wolf3d(t_wolf *data)
{
	data->map.len = data->map.height * data->map.width;
	data->map.depth = data->map.width > data->map.height
		? data->map.width : data->map.height;
	data->player.y = data->player.pos / data->map.width;
	data->player.x = data->player.pos - (data->player.y * data->map.width);
	data->player.y += 0.5;
	data->player.x += 0.5;
	data->player.fov = 3.14159f / 4;
	data->player.health = 200;
	data->player.health_max = 200;
	data->player.weapon = 0;
	data->map.sc_x = 4;
	data->key[KP] = 1;
	data->player.dirx = 1;
	data->player.diry = 0;
	data->player.planex = 0;
	data->player.planey = data->player.fov;
	data->key[MOUSE] = 1;
	data->obj_intens = 0.7;
	launch_game(data);
}
