/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/09 17:50:55 by sujo              #+#    #+#             */
/*   Updated: 2021/07/09 17:34:47 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_enter(char *s)
{
	size_t	idx;

	if (!s)
		return (-1);
	idx = 0;
	while (s[idx])
	{
		if (s[idx] == '\n')
			return (idx);
		idx++;
	}
	return (-1);
}

int	read_line(char **ret, char **s, int ent_idx)
{
	char	*buf;
	int		len;

	*ret = ft_substr(*s, 0, ent_idx);
	len = ft_strlen(*s) - ent_idx - 1;
	if (len == 0)
	{
		free(*s);
		*s = 0;
		return (1);
	}
	buf = ft_substr(*s, ent_idx + 1, len);
	free(*s);
	*s = buf;
	return (1);
}

int	read_line_2(char **ret, char **s, int buf_size, int ent_idx)
{
	if (buf_size == -1)
	{
		free(*s);
		*s = 0;
		return (-1);
	}
	if (buf_size == 0 && ent_idx == -1)
	{
		*ret = ft_strdup(*s);
		free(*s);
		*s = 0;
		return (0);
	}
	return (read_line(ret, s, ent_idx));
}

int	get_next_line(int fd, char **line)
{
	static char	*backup[256];
	char		buf[BUFFER_SIZE + 1];
	int			buf_size;
	int			ent_idx;

	if (!line || fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (-1);
	while (1)
	{
		buf_size = read(fd, buf, BUFFER_SIZE);
		if (buf_size <= 0)
			break ;
		buf[buf_size] = '\0';
		backup[fd] = ft_strjoin_gnl(backup[fd], buf);
		ent_idx = check_enter(backup[fd]);
		if (ent_idx != -1)
			return (read_line(line, &backup[fd], ent_idx));
	}
	buf[0] = '\0';
	if (buf_size == 0)
		backup[fd] = ft_strjoin_gnl(backup[fd], buf);
	ent_idx = check_enter(backup[fd]);
	return (read_line_2(line, &backup[fd], buf_size, ent_idx));
}
