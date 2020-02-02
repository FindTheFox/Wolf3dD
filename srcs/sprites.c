/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/31 16:51:51 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			sprites_monsters_maze(t_wolf *data)
{
	if (!(data->sprite[7].img = SDL_LoadBMP("img/monsters/monster1.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[8].img = SDL_LoadBMP("img/monsters/monster2.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[9].img = SDL_LoadBMP("img/monsters/monster3.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[10].img = SDL_LoadBMP("img/monsters/monster1atk.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[11].img = SDL_LoadBMP("img/monsters/monster2atk.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[12].img = SDL_LoadBMP("img/monsters/monster3atk.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[13].img = SDL_LoadBMP("img/monsters/monster1hit.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[14].img = SDL_LoadBMP("img/monsters/monster2hit.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[15].img = SDL_LoadBMP("img/monsters/monster3hit.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
}

void			sprites_monsters_asylum(t_wolf *data)
{
	if (!(data->sprite[8].img = SDL_LoadBMP("img/monsters/soldat.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[9].img = SDL_LoadBMP("img/monsters/mut.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[7].img = SDL_LoadBMP("img/monsters/doc.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[11].img = SDL_LoadBMP("img/monsters/soldatatk.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[12].img = SDL_LoadBMP("img/monsters/mutatk.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[10].img = SDL_LoadBMP("img/monsters/docatk.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[14].img = SDL_LoadBMP("img/monsters/soldathit.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[15].img = SDL_LoadBMP("img/monsters/muthit.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[13].img = SDL_LoadBMP("img/monsters/dochit.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
}

static void		sprites_object(t_wolf *data)
{
	if (!(data->sprite[3].img = SDL_LoadBMP("img/plante.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[4].img = SDL_LoadBMP("img/cage.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[5].img = SDL_LoadBMP("img/table.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[6].img = SDL_LoadBMP("img/rickportal.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[28].img = SDL_LoadBMP("img/rickportal.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
}

void			sprites_weapons(t_wolf *data)
{
	if (!(data->sprite[20].img = SDL_LoadBMP("img/weapons/hand.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[21].img = SDL_LoadBMP("img/weapons/hand2.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[22].img = SDL_LoadBMP("img/weapons/gun.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[23].img = SDL_LoadBMP("img/weapons/gunfire.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[24].img = SDL_LoadBMP("img/weapons/shotgun.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[25].img = SDL_LoadBMP("img/weapons/shotgunfire.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[26].img = SDL_LoadBMP("img/weapons/rafle.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
	if (!(data->sprite[27].img = SDL_LoadBMP("img/weapons/rafle2.bmp")))
		clean_exit(data, "wolf3d: load_sprites error", 0);
}

void			sprites(t_wolf *data)
{
	if (data->game == 1)
	{
		sprites_monsters_asylum(data);
		sprites_textures_asylum(data);
	}
	else if (data->game == 2)
	{
		sprites_textures_maze(data);
		sprites_monsters_maze(data);
	}
	else
	{
		sprites_textures(data);
		sprites_monsters_asylum(data);
	}
	sprites_object(data);
	sprites_weapons(data);
}
