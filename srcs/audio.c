/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 22:09:50 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/30 20:54:36 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			check_load(t_wolf *data)
{
	if (data->sound.fusil == NULL || data->sound.gun == NULL
			|| data->sound.hand == NULL || data->sound.nmiatk == NULL
			|| data->sound.nmideath == NULL || data->sound.nmihit == NULL
			|| data->sound.nmispawn == NULL || data->sound.playerdeath == NULL
			|| data->sound.playerhit == NULL || data->sound.playerspawn == NULL
			|| data->sound.shotgun == NULL || data->sound.switchgun == NULL
			|| data->sound.tic == NULL || data->sound.ingmusic == NULL
			|| data->sound.pausemusic == NULL)
		clean_exit(data, "wold3d: Mix_Load fail", 0);
}

void			audio_init(t_wolf *data)
{
	data->sound.token = 1;
	Mix_AllocateChannels(16);
	data->sound.hand = Mix_LoadWAV("sound/chunk/punch.wav");
	data->sound.gun = Mix_LoadWAV("sound/chunk/shoot2.wav");
	data->sound.fusil = Mix_LoadWAV("sound/chunk/shoot.wav");
	data->sound.shotgun = Mix_LoadWAV("sound/chunk/shotgun.wav");
	data->sound.nmihit = Mix_LoadWAV("sound/chunk/hitmonster.wav");
	data->sound.nmideath = Mix_LoadWAV("sound/chunk/dthmonster.wav");
	data->sound.nmispawn = Mix_LoadWAV("sound/chunk/spawnmonster.wav");
	data->sound.nmiatk = Mix_LoadWAV("sound/chunk/atkmonster.wav");
	data->sound.playerhit = Mix_LoadWAV("sound/chunk/playerhit.wav");
	data->sound.playerdeath = Mix_LoadWAV("sound/chunk/playerdeath.wav");
	data->sound.playerspawn = Mix_LoadWAV("sound/chunk/playerspawn.wav");
	data->sound.switchgun = Mix_LoadWAV("sound/chunk/switchgun.wav");
	data->sound.tic = Mix_LoadWAV("sound/chunk/tic.wav");
	data->sound.ingmusic = Mix_LoadMUS("sound/music/SignOfEvil.wav");
	data->sound.pausemusic = Mix_LoadMUS("sound/music/AtDoomsGate.wav");
	check_load(data);
}

void			free_sound(t_wolf *data)
{
	Mix_HaltChannel(-1);
	Mix_FreeMusic(data->sound.ingmusic);
	Mix_FreeMusic(data->sound.pausemusic);
	Mix_FreeChunk(data->sound.hand);
	Mix_FreeChunk(data->sound.gun);
	Mix_FreeChunk(data->sound.fusil);
	Mix_FreeChunk(data->sound.shotgun);
	Mix_FreeChunk(data->sound.nmihit);
	Mix_FreeChunk(data->sound.nmideath);
	Mix_FreeChunk(data->sound.nmispawn);
	Mix_FreeChunk(data->sound.nmiatk);
	Mix_FreeChunk(data->sound.playerhit);
	Mix_FreeChunk(data->sound.playerdeath);
	Mix_FreeChunk(data->sound.playerspawn);
	Mix_FreeChunk(data->sound.switchgun);
	Mix_FreeChunk(data->sound.tic);
	Mix_AllocateChannels(0);
	data->sound.token = 0;
}

void			play_sound(t_wolf *data, Mix_Chunk *chunk, int channel)
{
	if (Mix_PlayChannelTimed(channel, chunk, 0, 500) == -1)
		clean_exit(data, "Wolf3d: Play sound fail", 0);
}

void			play_music(t_wolf *data, Mix_Music *music)
{
	if (Mix_PlayingMusic() == 0)
	{
		if (Mix_PlayMusic(music, -1))
			clean_exit(data, "wolf3d: Mix_PlayMusic fail", 0);
	}
	else
	{
		Mix_HaltMusic();
		if (music == NULL)
			return ;
		else if (Mix_PlayMusic(music, -1))
			clean_exit(data, "wolf3d: Mix_PlayMusic fail", 0);
	}
}
