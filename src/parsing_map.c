/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 19:55:06 by sujo              #+#    #+#             */
/*   Updated: 2021/07/09 13:41:03 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "so_long.h"

static void	map_error(void)
{
	write(1, "Error\n", 6);
	exit(1);
}

static int	check_map(char *filename, t_map *map)
{
	char	*line;
	int		fd;
	int		size;
	int		height;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		map_error();
	size = 0;
	height = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (!size)
			size = ft_strlen(line);
		if (size != ft_strlen(line))
			map_error();
		free(line);
		height++;
	}
	if (ft_strlen(line) != 0 && size != ft_strlen(line))
		map_error();
	free(line);
	map->height = height;
	return (size);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*ptr;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (0);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 + len2 == 0)
		return (ft_strdup(""));
	result = (char *)malloc(len1 + len2 + 1);
	if (!result)
		return (0);
	ptr = result;
	ptr = ft_str_copy(result, (char *)s1);
	ptr = ft_str_copy(ptr, (char *)s2);
	return (result);
}

void	parsing_map(t_map *map, char *filename)
{
	char	*line;
	char	*path;
	int		fd;
	int		i;

	i = -1;
	path = ft_strjoin("map/", filename);
	map->width = check_map(path, map);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		map_error();
	map->map = (char **)malloc(sizeof(char *) * map->height);
	while (get_next_line(fd, &line) > 0)
		map->map[++i] = line;
	map->height = ++i;
	if (ft_strlen(line) != 0)
	{
		map->map[i] = line;
		map->height += 1;
	}
	else
		free(line);
	map->cnt = 0;
	map->collect = 0;
	valid_map(map);
}
