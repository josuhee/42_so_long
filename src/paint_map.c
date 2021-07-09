/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 21:13:48 by sujo              #+#    #+#             */
/*   Updated: 2021/07/09 13:39:08 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	paint_background(t_mlx *mlx, int width, int height)
{
	t_back	b;
	int		i;
	int		j;

	b.img_ptr = mlx_new_image(mlx->mlx_ptr, width, height);
	b.data = (int *)mlx_get_data_addr(b.img_ptr, &b.bpp, &b.size_l, &b.endian);
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			b.data[i * width + j] = 0xABDD93;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, b.img_ptr, 0, 0);
}

void	print_img(t_mlx *mlx, char *filename, int x, int y)
{
	void	*img;
	int		w;
	int		h;

	h = 0;
	w = 0;
	img = mlx_xpm_file_to_image(mlx->mlx_ptr, filename, &w, &h);
	if (h == 0 || w == 0)
	{
		perror("img");
		exit(1);
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img, x, y);
}

static void	put_string_mlx(t_map *map, t_mlx *mlx)
{
	char	*cnt;
	int		x;
	int		y;

	x = map->y * 72;
	y = map->x * 72;
	cnt = ft_itoa(map->cnt);
	mlx_string_put(mlx->mlx_ptr, mlx->win, x, y, 0x3162C7, cnt);
	free(cnt);
}

static void	set_img(t_mlx *mlx, t_img *img, t_point p, char ch)
{
	if (ch == '1')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img->wall, p.x, p.y);
	if (ch == 'C')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img->collect, p.x, p.y);
	if (ch == 'E')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img->exit, p.x, p.y);
	if (ch == 'A')
		mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img->die, p.x, p.y);
}

void	paint_map(t_mlx *mlx, t_map *map, t_img *img, char *player)
{
	char	*cnt;
	int		i;
	int		j;

	paint_background(mlx, map->width * 72, map->height * 72);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			if (map->map[i][j] == '1')
				set_img(mlx, img, (t_point){j * 72, i * 72}, '1');
			if (map->map[i][j] == 'C')
				set_img(mlx, img, (t_point){j * 72, i * 72}, 'C');
			if (map->map[i][j] == 'E')
				set_img(mlx, img, (t_point){j * 72, i * 72}, 'E');
			if (map->map[i][j] == 'A')
				set_img(mlx, img, (t_point){j * 72, i * 72}, 'A');
			if (map->map[i][j] == 'P')
				print_img(mlx, player, j * 72, i * 72);
		}
	}
	put_string_mlx(map, mlx);
}
