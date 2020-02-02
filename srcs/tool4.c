/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 19:50:05 by saneveu           #+#    #+#             */
/*   Updated: 2020/02/02 20:49:06 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

void			choose_game(t_wolf *d, char *game)
{
	if (ft_strequ(game, "asylum"))
	{
		d->game = 1;
		d->style = 0;
		d->strgame = game;
		d->floorstyle = 2;
		d->fog = 3;
	}
	else if (ft_strequ(game, "maze"))
	{
		d->game = 2;
		d->style = 1;
		d->strgame = game;
		d->floorstyle = 0;
		d->fog = 1;
	}
	else
	{
		d->game = 0;
		d->style = 2;
		d->strgame = "wolf3d";
		d->floorstyle = 1;
		d->fog = 2;
	}
}
