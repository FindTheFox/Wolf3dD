/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_monster.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:38:46 by bebosson          #+#    #+#             */
/*   Updated: 2020/01/15 21:28:03 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			object_minimap(t_wolf *data, t_object *list)
{
	int			i;
	SDL_Rect	rect;

	i = 0;
	if (list == NULL)
		return ;
	rect.h = 4;
	rect.w = 4;
	while (list)
	{
		if (list->type > 2 && list->type < 10)
		{
			rect.x = list->x * W_WIDTH
				/ (data->map.sc_x * data->map.width);
			rect.y = list->y * W_HEIGHT
				/ (data->map.sc_x * data->map.height);
			set_rect_to_screen(data, &rect, 0);
			SDL_RenderFillRect(data->renderer, &rect);
		}
		list = list->next;
		i++;
	}
}

void			draw_fps(t_wolf *data)
{
	char		*tmp;
	char		*fps;
	char		*kill;
	SDL_Rect	rect;

	tmp = ft_itoa(data->fps);
	fps = ft_strfjoin("fps ", tmp, 2);
	rect = (SDL_Rect){0, W_HEIGHT / data->map.sc_x - 5,
		10 * data->map.sc_x, 3 * data->map.sc_x};
	data->policep = data->police3;
	set_write_to_screen(data, rect, 0, fps);
	tmp = ft_itoa(data->kill_score);
	kill = ft_strjoin("kill ", tmp);
	rect = (SDL_Rect){W_WIDTH / data->map.sc_x - 50,
		W_HEIGHT / data->map.sc_x - 5,
			10 * data->map.sc_x, 3 * data->map.sc_x};
	set_write_to_screen(data, rect, 0, kill);
	ft_strdel(&tmp);
	ft_strdel(&fps);
	ft_strdel(&kill);
}
