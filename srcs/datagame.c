/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datagame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 17:52:38 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/02 20:18:09 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static void		help_get_list(t_wolf *data, t_object *list)
{
	list->speed = 0.2f;
	list->si = list->type;
	list->i = list->x + data->map.width * list->y;
	list->sprite = data->sprite[list->si];
	list->x -= 0.5;
	list->y += 0.5;
}

static void		get_list(t_wolf *data, t_object *list, int min, int max)
{
	t_object	*head;
	int			i;

	if (list == NULL)
		return ;
	head = list;
	i = -1;
	while (++i < data->map.len)
		if (data->map.map[i] >= min && data->map.map[i] <= max)
		{
			data->map.map[i] == 28 ? set_end_pt(data, i) : 0;
			list->y = i / data->map.width;
			list->x = i - (list->y * data->map.width) + 1;
			list->type = data->map.map[i];
			list->hp = get_objhp(data, list);
			list->hp_max = list->hp;
			help_get_list(data, list);
			lst_pushback(list, (t_object *)ft_memalloc(sizeof(t_object)));
			if (list == NULL)
				clean_exit(data, "wolf3d: malloc error", 0);
			list = list->next;
		}
	list = head;
}

static void		weapons_data(t_wolf *data)
{
	data->player.wdata[0].damage = 60;
	data->player.wdata[0].delay = 10;
	data->player.wdata[0].range = 2;
	data->player.wdata[0].si = 20;
	data->player.wdata[1].damage = 30;
	data->player.wdata[1].delay = 15;
	data->player.wdata[1].range = data->map.depth;
	data->player.wdata[1].si = 22;
	data->player.wdata[2].damage = 180;
	data->player.wdata[2].delay = 30;
	data->player.wdata[2].range = data->map.depth;
	data->player.wdata[2].si = 24;
	data->player.wdata[3].damage = 40;
	data->player.wdata[3].delay = 5;
	data->player.wdata[3].range = data->map.depth;
	data->player.wdata[3].si = 26;
}

void			load_datagame(t_wolf *data)
{
	SDL_GetWindowPosition(data->pwindow, &data->wx, &data->wy);
	sprites(data);
	if (!(data->object = (t_object *)ft_memalloc(sizeof(t_object))))
		clean_exit(data, "wolf3d: malloc error", 0);
	if (!(data->monster = (t_object *)ft_memalloc(sizeof(t_object))))
		clean_exit(data, "wolf3d: malloc error", 0);
	if (!(data->end_flag = (t_object *)ft_memalloc(sizeof(t_object))))
		clean_exit(data, "wolf3d: malloc error", 0);
	get_list(data, data->object, 3, 5);
	get_list(data, data->monster, 6, 9);
	get_list(data, data->end_flag, 28, 28);
	if (!(data->screen = new_surface(W_WIDTH, W_HEIGHT)))
		clean_exit(data, "wolf3d: error creating RGB surface", 0);
	get_nodes(data);
	weapons_data(data);
}
