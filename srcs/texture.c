/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 18:17:01 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/16 19:06:32 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			sprites_textures_maze(t_wolf *data)
{
	if (!(data->sprite[16].img = SDL_LoadBMP("img/textures/wall.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[17].img = SDL_LoadBMP("img/textures/wall.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[18].img = SDL_LoadBMP("img/textures/wall.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[19].img = SDL_LoadBMP("img/textures/wall.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[1].img = SDL_LoadBMP("img/textures/stone.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[0].img = SDL_LoadBMP("img/textures/ceilling.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[2].img = SDL_LoadBMP("img/maze.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
}

void			sprites_textures_asylum(t_wolf *data)
{
	if (!(data->sprite[16].img = SDL_LoadBMP("img/textures/capwall.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
	if (!(data->sprite[17].img = SDL_LoadBMP("img/textures/capwall.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
	if (!(data->sprite[18].img = SDL_LoadBMP("img/textures/capwall2.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
	if (!(data->sprite[19].img = SDL_LoadBMP("img/textures/capwall2.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
	if (!(data->sprite[1].img = SDL_LoadBMP("img/textures/capwall.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
	if (!(data->sprite[0].img = SDL_LoadBMP("img/textures/capwall2.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
	if (!(data->sprite[2].img = SDL_LoadBMP("img/asylum.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
}

void			sprites_textures(t_wolf *data)
{
	if (!(data->sprite[16].img = SDL_LoadBMP("img/textures/evil-eye.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
	if (!(data->sprite[17].img = SDL_LoadBMP("img/textures/magic.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
	if (!(data->sprite[18].img = SDL_LoadBMP("img/textures/magic-star.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
	if (!(data->sprite[19].img = SDL_LoadBMP("img/textures/unicorn.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
	if (!(data->sprite[1].img = SDL_LoadBMP("img/textures/water.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
	if (!(data->sprite[0].img = SDL_LoadBMP("img/textures/wood.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
	if (!(data->sprite[2].img = SDL_LoadBMP("img/test.bmp")))
		clean_exit(data, "wolf3d: load_sprites error\n", 0);
}
