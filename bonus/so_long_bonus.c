/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:53:34 by sujo              #+#    #+#             */
/*   Updated: 2021/07/09 17:33:38 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	*init_img_util(t_mlx *mlx, char *filename)
{
	void	*result;
	int		width;
	int		height;

	width = 0;
	height = 0;
	result = mlx_xpm_file_to_image(mlx->mlx_ptr, filename, &width, &height);
	if (height == 0 || width == 0)
	{
		perror("img");
		exit(1);
	}
	return (result);
}

static void	init_img(t_mlx *mlx, t_img *img)
{
	img->player1 = init_img_util(mlx, "img/player1.xpm");
	img->player2 = init_img_util(mlx, "img/player2.xpm");
	img->die = init_img_util(mlx, "img/die.xpm");
	img->exit = init_img_util(mlx, "img/exit.xpm");
	img->wall = init_img_util(mlx, "img/wall.xpm");
	img->collect = init_img_util(mlx, "img/collect.xpm");
}

static int	program_close(void)
{
	write(1, "Exit program!\n", 14);
	exit(0);
}

static int	player_loop(t_map *map)
{
	static int	flag;
	int			x;
	int			y;

	if (flag < 10)
	{
		paint_map(&map->mlx, map, &map->img, "img/player1.xpm");
		flag++;
	}
	else if (flag < 20)
	{
		paint_map(&map->mlx, map, &map->img, "img/player2.xpm");
		flag++;
	}
	else
	{
		search_player(map);
		paint_map(&map->mlx, map, &map->img, "img/player2.xpm");
		flag = 0;
	}
	x = map->y * 72 + 72;
	y = map->x * 72;
	if (map->collect == 1)
		mlx_string_put(map->mlx.mlx_ptr, map->mlx.win, x, y, 0xFF0000, "Get !");
	return (0);
}

void	so_long(char *filename)
{
	t_mlx	mlx;
	t_map	map;
	t_img	img;
	int		x;
	int		y;

	parsing_map(&map, filename);
	mlx.mlx_ptr = mlx_init();
	x = map.width * 72;
	y = map.height * 72;
	mlx.win = mlx_new_window(mlx.mlx_ptr, x, y, "so_long");
	init_img(&mlx, &img);
	paint_map(&mlx, &map, &img, "img/player1.xpm");
	map.mlx = mlx;
	map.img = img;
	key_event(&mlx, &map);
	mlx_loop_hook(mlx.mlx_ptr, &player_loop, &map);
	mlx_hook(mlx.win, X_EVENT_KEY_EXIT, 0, &program_close, NULL);
	mlx_loop(mlx.mlx_ptr);
	mlx_clear_window(mlx.mlx_ptr, mlx.win);
}
