/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 22:57:38 by sujo              #+#    #+#             */
/*   Updated: 2021/07/09 12:11:14 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void		map_error(void)
{
	write(1, "Error\n", 6);
	exit(1);
}

static void		check_char(t_check *check, char ch)
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

//bonus
/*
1. enemy를 둘 수 있는 공간이 없는 경우
2. dfs로 플레이어를 찾을 수 없는 경우

*/
static void		enemy(t_map *map)
{
	srand(time(NULL));

	if (map->empty == 0)
		map_error();
	while (1)
	{
		map->junmkang_x = rand() % map->height;
		map->junmkang_y = rand() % map->width;
		init_arr(map);
		dfs(map->x, map->y, 0, map);
		if (map->dfs.visit[map->x][map->y] == 0)
		{
			write(1, "enemy location error\n", 21);
			exit(1);
		}
		if (map->map[map->junmkang_x][map->junmkang_y] == '0')
		{
			map->map[map->junmkang_x][map->junmkang_y] = 'A';
			break;
		}
		free(map->dfs.arr[0]);
		free(map->dfs.arr);
		free(map->dfs.visit[0]);
		free(map->dfs.visit);
	}
}

void			valid_map(t_map *map)
{
	int		i;
	int		j;
	t_check	check;

	i = 0;
	check = (t_check){0, 0, 0};
	map->empty = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (i == 0 || j == 0 || i == map->height - 1 || j == map->width - 1)
				if (map->map[i][j] != '1')
					map_error();
			if (map->map[i][j] != '0')
				check_char(&check, map->map[i][j]);
			else
				map->empty = map->empty + 1;
			if (map->map[i][j] == 'P')
			{
				map->x = i;
				map->y = j;
			}
			j++;
		}
		i++;
	}
	if (check.collect == 0 || check.exit == 0)
		map_error();
	enemy(map);
}
