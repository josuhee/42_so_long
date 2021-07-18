/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 14:25:30 by sujo              #+#    #+#             */
/*   Updated: 2021/07/18 21:48:04 by sujo             ###   ########.fr       */
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

static void	game_clear(void)
{
	write(1, "\033[93mGame Clear\033[0m\n", 20);
	exit(0);
}

static void	print_cnt(t_map *map)
{
	char	*str;

	map->cnt++;
	str = ft_itoa(map->cnt);
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	free(str);
}

static void	player_location(t_map *map, int x, int y)
{
	if (x >= 0 && y >= 0 && x < map->height && y < map->width)
	{
		if (map->map[x][y] == 'E')
		{
			if (valid_exit(map))
				game_clear();
		}
		else if (map->map[x][y] == 'A')
		{
			write(1, "\033[92mGame Over\033[0m \033[01;31mㅋ\033[0m\n", 35);
			exit(0);
		}
		else if (map->map[x][y] != '1')
		{
			map->collect = 0;
			if (map->map[x][y] == 'C')
				map->collect = 1;
			map->map[map->x][map->y] = '0';
			map->x = x;
			map->y = y;
			map->map[x][y] = 'P';
			paint_map(&map->mlx, map, &map->img, "img/player1.xpm");
			print_cnt(map);
		}
	}
}

int	key_press(int keycode, t_map *map)
{
	if (keycode == KEY_ESC)
	{
		write(1, "You Enter the ESC Key. Bye :D\n", 30);
		exit(0);
	}
	if (keycode == KEY_W || keycode == KEY_UP)
		player_location(map, map->x - 1, map->y);
	if (keycode == KEY_S || keycode == KEY_DOWN)
		player_location(map, map->x + 1, map->y);
	if (keycode == KEY_D || keycode == KEY_RIGHT)
		player_location(map, map->x, map->y + 1);
	if (keycode == KEY_A || keycode == KEY_LEFT)
		player_location(map, map->x, map->y - 1);
	return (0);
}
