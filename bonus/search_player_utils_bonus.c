/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_player_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 17:17:16 by sujo              #+#    #+#             */
/*   Updated: 2021/07/09 17:33:36 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	set_dfs_arg(t_map *map, int *min, int x, int y)
{
	*min = map->dfs.arr[x][y];
	map->min_x = x;
	map->min_y = y;
}

void	game_over(void)
{
	write(1, "\033[92mGame Over\033[0m \033[01;31mㅋ\033[0m\n", 35);
	exit(0);
}
