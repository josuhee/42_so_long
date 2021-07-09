/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 15:53:49 by sujo              #+#    #+#             */
/*   Updated: 2021/07/09 12:18:17 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_arr(t_map *map)
{
	int i;
	int j;

	map->dfs.arr = (int **)malloc(sizeof(int *) * map->height);
	map->dfs.visit = (int **)malloc(sizeof(int *) * map->height);
	if (!map->dfs.arr || !map->dfs.visit)
		exit(1);
	i = 0;
	while (i < map->height)
	{
		j = 0;
		map->dfs.arr[i] = (int *)malloc(sizeof(int) * map->width);
		map->dfs.visit[i] = (int *)malloc(sizeof(int) * map->width);
		while (j < map->width)
		{
			if (!map->dfs.arr[i] || !map->dfs.visit[i])
				exit(1);
			if (map->map[i][j] == '0')
				map->dfs.arr[i][j] = 0;
			else
				map->dfs.arr[i][j] = -1;
			map->dfs.visit[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	dfs(int x, int y, int cnt, t_map *map)
{
	map->dfs.visit[x][y] = 1;
	map->dfs.arr[x][y] = cnt;

	if (map->junmkang_x == x && map->junmkang_y == y)
		return ;
	if (x - 1 >= 0)
		if ((map->dfs.visit[x-1][y] && map->dfs.arr[x-1][y] > cnt + 1) || (!map->dfs.visit[x-1][y] && map->dfs.arr[x - 1][y] == 0))
			dfs(x - 1, y, cnt + 1, map);
	if (x + 1 < map->height)
		if ((map->dfs.visit[x+1][y] && map->dfs.arr[x+1][y] > cnt + 1) || (!map->dfs.visit[x+1][y] && map->dfs.arr[x + 1][y] == 0))
			dfs(x + 1, y, cnt + 1, map);
	if (y - 1 >= 0)
		if ((map->dfs.visit[x][y - 1] && map->dfs.arr[x][y-1] > cnt + 1) || (!map->dfs.visit[x][y-1] && map->dfs.arr[x][y-1] == 0))
			dfs(x, y - 1, cnt + 1, map);
	if (y + 1 < map->width)
		if ((map->dfs.visit[x][y + 1] && map->dfs.arr[x][y+1] > cnt + 1) || (!map->dfs.visit[x][y+1] && map->dfs.arr[x][y+1] == 0))
			dfs(x, y + 1, cnt + 1, map);
	return ;
}

void		min(t_map *map)
{
	int x;
	int y;
	int min;

	map->min_x = map->junmkang_x;
	map->min_y = map->junmkang_y;
	x = map->junmkang_x;
	y = map->junmkang_y;
	if (x - 1 >= 0 && map->dfs.visit[x-1][y])
	{
		min = map->dfs.arr[x-1][y];
		map->min_x = x - 1;
		map->min_y = y;
	}
	if (x + 1 <= map->height && min > map->dfs.arr[x+1][y] && map->dfs.visit[x+1][y])
	{
		min = map->dfs.arr[x+1][y];
		map->min_x = x + 1;
		map->min_y = y;
	}
	if (y - 1 >= 0 && min > map->dfs.arr[x][y - 1]&& map->dfs.visit[x][y-1])
	{
		min = map->dfs.arr[x][y - 1];
		map->min_x = x;
		map->min_y = y - 1;
	}
	if (y + 1 < map->width && min > map->dfs.arr[x][y + 1]&& map->dfs.visit[x][y+1])
	{
		min = map->dfs.arr[x][y + 1];
		map->min_x = x;
		map->min_y = y + 1;
	}
	map->map[map->junmkang_x][map->junmkang_y] = '0';
	map->junmkang_x = map->min_x;
	map->junmkang_y = map->min_y;
	map->map[map->min_x][map->min_y] = 'A';
	if (map->x == map->junmkang_x && map->y == map->junmkang_y)
		exit(0);
}

void		search_player(t_map *map)
{
	int ret;

	init_arr(map);
	dfs(map->x, map->y, 0, map);
	min(map);
	free(map->dfs.arr[0]);
	free(map->dfs.arr);
	free(map->dfs.visit[0]);
	free(map->dfs.visit);
}
