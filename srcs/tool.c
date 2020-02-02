/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 15:05:22 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/02 20:41:08 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			lst_free(t_object *list)
{
	t_object	*tmp;

	while (list)
	{
		tmp = list->next;
		ft_memdel((void **)&list);
		if (tmp)
			list = tmp;
	}
}

int				lst_len(t_object *list)
{
	int			i;
	t_object	*tmp;

	if (list == NULL)
		return (0);
	tmp = list;
	i = 0;
	while (tmp)
	{
		++i;
		tmp = tmp->next;
	}
	return (i);
}

void			lst_pushback(t_object *list, t_object *node)
{
	t_object	*head;

	head = list;
	if (node == NULL)
		lst_free(head);
	if (list)
	{
		while (list->next)
			list = list->next;
		if (!(list->next = node))
		{
			lst_free(head);
			return ;
		}
		list = head;
	}
}

void			free_surfaces(t_wolf *data, int flag)
{
	int	i;

	i = SNB;
	while (i-- && flag == 0)
		if (data->sprite[i].img)
			SDL_FreeSurface(data->sprite[i].img);
	if (data->screen && flag == 0)
		SDL_FreeSurface(data->screen);
	else if (flag == 1)
	{
		SDL_FreeSurface(data->sprite[16].img);
		SDL_FreeSurface(data->sprite[17].img);
		SDL_FreeSurface(data->sprite[18].img);
		SDL_FreeSurface(data->sprite[19].img);
		SDL_FreeSurface(data->sprite[1].img);
		SDL_FreeSurface(data->sprite[0].img);
		SDL_FreeSurface(data->sprite[2].img);
	}
}

void			free_ttf(t_wolf *data)
{
	TTF_CloseFont(data->police);
	TTF_CloseFont(data->police2);
	TTF_CloseFont(data->police3);
	TTF_Quit();
}

/*
**void after_main() __attribute__((destructor));
**
**void after_main()
**{
**	while (1);
**}
*/
