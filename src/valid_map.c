/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 22:57:38 by sujo              #+#    #+#             */
/*   Updated: 2021/07/14 14:21:56 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	map_error(void)
{
	write(1, "Error\n", 6);
	exit(1);
}

static void	check_char(t_check *check, char ch)
{
	if (ch != 'P' && ch != '1' && ch != 'C' && ch != 'E' && ch != 'A')
		map_error();
	if (ch == 'P')
	{
		if (check->player == 1)
			map_error();
		else
			check->player = 1;
	}
	if (ch == 'E')
		check->exit = 1;
	if (ch == 'C')
		check->collect = 1;
}

static void	player_place(t_map *map, int x, int y, char ch)
{
	if (ch == 'P')
	{
		map->x = x;
		map->y = y;
	}
	if (ch == '0')
		map->empty = map->empty + 1;
}

void	valid_map(t_map *map)
{
	int		i;
	int		j;
	t_check	check;

	i = -1;
	check = (t_check){0, 0, 0};
	map->empty = 0;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (i == 0 || j == 0 || i == map->height - 1 || j == map->width - 1)
				if (map->map[i][j] != '1')
					map_error();
			if (map->map[i][j] != '0')
				check_char(&check, map->map[i][j]);
			player_place(map, i, j, map->map[i][j]);
		}
	}
	if (check.collect == 0 || check.exit == 0)
		map_error();
}
