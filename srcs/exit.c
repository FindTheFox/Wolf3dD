/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/02 20:24:12 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/02 20:39:40 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

/*
** SDL_DestroyRenderer(data->renderer);
*/

void			clean_exit(t_wolf *data, char *str, int token)
{
	if (data)
	{
		if (data->sdl_on)
		{
			free_surfaces(data, 0);
			if (data->sound.token == 1)
				free_sound(data);
			Mix_CloseAudio();
			free_ttf(data);
			if (data->pwindow)
				SDL_DestroyWindow(data->pwindow);
			SDL_Quit();
		}
		ft_strdel(&data->str);
		ft_memdel((void **)&data->map.map);
		lst_free(data->object);
		lst_free(data->monster);
		lst_free(data->end_flag);
		ft_memdel((void **)&data->pfdata.list);
	}
	if (str)
		ft_putendl_fd(str, 2);
	exit(token ? EXIT_SUCCESS : EXIT_FAILURE);
}
