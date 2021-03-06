/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 15:46:37 by sujo              #+#    #+#             */
/*   Updated: 2021/07/18 21:42:10 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx_opengl/mlx.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_back
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_back;

typedef struct s_img
{
	void		*player1;
	void		*player2;
	void		*collect;
	void		*exit;
	void		*die;
	void		*wall;
}				t_img;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win;
}				t_mlx;

typedef struct s_dfs
{
	int	**arr;
	int	**visit;
}				t_dfs;

typedef struct s_map
{
	struct s_mlx	mlx;
	struct s_img	img;
	struct s_dfs	dfs;
	char			**map;
	int				junmkang_x;
	int				junmkang_y;
	int				width;
	int				height;
	int				cnt;
	int				collect;
	int				x;
	int				y;
	int				min_x;
	int				min_y;
	int				empty;
}					t_map;

typedef struct s_check
{
	int	player;
	int	exit;
	int	collect;
}				t_check;

typedef struct s_point
{
	int	x;
	int	y;
}				t_point;

/*
* Key Event
*/
# define X_EVENT_KEY_EXIT 17
# define X_EVENT_KEY_PRESS 2
# define KEY_ESC 53
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126

void	so_long(char *filename);
void	parsing_map(t_map *map, char *filename);
void	valid_map(t_map *map);
void	paint_map(t_mlx *mlx, t_map *map, t_img *img, char *player);
void	search_player(t_map *map);
void	game_over(void);
int		key_press(int keycode, t_map *map);
char	*ft_itoa(int num);

#endif
