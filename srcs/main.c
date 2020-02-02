/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saneveu <saneveu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:47:19 by saneveu           #+#    #+#             */
/*   Updated: 2020/01/31 19:12:33 by saneveu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf3d.h"

static int		is_goodvalue(t_wolf *data, char c, int i)
{
	if (c >= '0' && c <= '7')
	{
		if (c == '7')
			data->map.map[i] = 28;
		else
		{
			if (data->player.pos == -1 && c == '2')
				data->player.pos = i;
			data->map.map[i] = c - '0';
		}
		return (1);
	}
	else
		return (0);
}

static int		parse_map(t_wolf *data)
{
	int		i;
	char	*tmp;

	if (data->map.len < 25)
		clean_exit(data, "wolf3d: map too small", 0);
	data->player.pos = -1;
	i = 0;
	tmp = data->str;
	while (tmp && tmp[i])
	{
		while (is_goodvalue(data, tmp[i], i))
			++i;
		if (tmp[i] == '\n' && tmp[i + 1] != '\n')
		{
			data->map.width = data->map.width < 1 ? i : data->map.width;
			++tmp;
			++data->map.height;
		}
		else
			break ;
	}
	if (data->player.pos == -1)
		clean_exit(data, "wolf3d: map error: no player found", 0);
	data->map.width = data->map.width < 1 ? 1 : data->map.width;
	return (i % data->map.width == tmp[i] ? 1 : 0);
}

static int		get_map(t_wolf *data, int file)
{
	int		r;
	char	buff[BUFF_SIZE];

	if (file == -1)
		clean_exit(data, "wolf3d: open error", 0);
	if (!(data->str = (char *)ft_memalloc(1)))
		clean_exit(data, "wolf3d: malloc error", 0);
	while (data->str && (r = read(file, buff, BUFF_SIZE)))
	{
		if (r == -1)
			clean_exit(data, "wolf3d: read error", 0);
		buff[r] = '\0';
		if (!(data->str = ft_strfjoin(data->str, buff, 1)))
			clean_exit(data, "wolf3d: malloc error", 0);
	}
	data->map.len = (int)ft_strlen(data->str) + 1;
	if (!(data->map.map = (int *)ft_memalloc(sizeof(int) * data->map.len)))
		clean_exit(data, "wolf3d: malloc error", 0);
	close(file);
	return (parse_map(data));
}

int				check_dotwolf(char *str)
{
	int i;

	i = ft_strlen(str);
	if (!ft_strequ((str + i - 5), ".wolf"))
		return (0);
	else
		return (1);
}

int				main(int ac, char **av)
{
	t_wolf	data;

	if (ac == 2 || ac == 3)
	{
		ft_memset(&data, 0, sizeof(t_wolf));
		choose_game(&data, av[2]);
		if (!check_dotwolf(av[1]))
			clean_exit(&data, "wolf3d: not valid format\nuse .wolf file", 0);
		else if (get_map(&data, open(av[1], O_NOCTTY | O_RDONLY
			| O_NONBLOCK)) == 1)
		{
			wolf3d(&data);
			clean_exit(&data, NULL, 1);
		}
		else
			clean_exit(&data, "wolf3d: map error (parse error)", 0);
	}
	else
	{
		ft_putstr_fd("wolf3d: usage: ./wolf3d [ valid_map ]\n", 2);
		ft_putstr_fd("choose the game with arg [asylum][maze][test]\n", 2);
	}
	return (EXIT_FAILURE);
}
