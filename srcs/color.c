/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 19:55:08 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/30 19:56:39 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

int			rgb_to_hsv(int r, int g, int b)
{
	return ((r * 256 * 256) + (g * 256) + b);
}

t_rgba		fill_rgb(int c)
{
	t_rgba rgb;

	rgb.r = c / (256 * 256);
	rgb.g = (c / 256) % 256;
	rgb.b = c % 256;
	return (rgb);
}
