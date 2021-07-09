/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:25:30 by sujo              #+#    #+#             */
/*   Updated: 2021/07/09 12:39:28 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	valid_exit(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (map->map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static void	player_location(t_map *map, int x, int y)
{
	if (x >= 0 && y >= 0 && x < map->height && y < map->width)
	{
		if (map->map[x][y] == 'E')
		{
			if (valid_exit(map))
				exit(0);
			else
				return ;
		}
		if (map->map[x][y] == 'A')
			exit(0);
		if (map->map[x][y] != '1')
		{
			map->collect = 0;
			if (map->map[x][y] == 'C')
				map->collect = 1;
			map->map[map->x][map->y] = '0';
			map->x = x;
			map->y = y;
			map->map[x][y] = 'P';
			paint_map(&map->mlx, map, &map->img, "img/player1.xpm");
			map->cnt++;
		}
	}
}

int	key_press(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_W || keycode == KEY_UP)
	{
		player_location(map, map->x - 1, map->y);
	}
	if (keycode == KEY_S || keycode == KEY_DOWN)
	{
		player_location(map, map->x + 1, map->y);
	}
	if (keycode == KEY_D || keycode == KEY_RIGHT)
	{
		player_location(map, map->x, map->y + 1);
	}
	if (keycode == KEY_A || keycode == KEY_LEFT)
	{
		player_location(map, map->x, map->y - 1);
	}
	return (0);
}

void	key_event(t_mlx *mlx, t_map *map)
{
	mlx_hook(mlx->win, X_EVENT_KEY_PRESS, 0, &key_press, map);
}
