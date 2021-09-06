/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 19:55:06 by sujo              #+#    #+#             */
/*   Updated: 2021/07/14 13:59:14 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	map_error(void)
{
	write(1, "Error\nInvalid Map\n", 18);
	exit(1);
}

static int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

static int	check_map(char *filename, t_map *map)
{
	char	*line;
	int		fd;
	size_t	size;
	int		height;

	fd = open(filename, O_RDONLY);
	if (fd < 0 || ft_strcmp(".ber", &filename[ft_strlen(filename) - 4]))
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
	if (ft_strlen(line) != 0 && ++map->height)
		map->map[i] = line;
	else
		free(line);
	map->cnt = 0;
	map->collect = 0;
	free(path);
	valid_map(map);
}
