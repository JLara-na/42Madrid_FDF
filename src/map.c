/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:40:51 by jlara-na          #+#    #+#             */
/*   Updated: 2023/12/14 20:24:39 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/FDF.h"

static void	map_start(t_map *map)
{
	map->height = 0;
	map->width = 0;
}

static void	map_mesure(t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		terminate(ERROR_IMEM, map);
	x_mesure(map, line);
	line_check(map, line);
	free(line);
	while (line)
	{
		line = get_next_line(fd);
		if (line)
		{
			line_check(map, line);
			free(line);
		}
	}
	close (fd);
}

static void	map_alocator(t_map *map)
{
	int	x;

	x = -1;
	if (map->height && map->width)
	{
		map->points = ft_calloc(map->width + 1, sizeof(t_point));
		if (!map->points)
			terminate(ERROR_MALLOC, map);
		while (x++ < map->width)
		{
			map->points[x] = ft_calloc(map->height + 1, sizeof(t_point));
			if (!map->points[x])
				terminate(ERROR_MALLOC, map);
		}
	}
}

static void	row_loader(t_map *map, int fd, int y)
{
	char	*row;
	char	**split;
	int		i;

	i = 0;
	row = get_next_line(fd);
	split = ft_split(row, ' ');
	point_loader(map, split, y);
	color_loader(map, split, y);
	free(row);
	while (i < map->width)
		free(split[i++]);
	free(split);
}

void	map_loader(t_map *map, char *path)
{
	int	fd;
	int	y;

	y = 0;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		terminate(ERROR_IFD, map);
	map_start(map);
	map_mesure(map, fd);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		terminate(ERROR_IFD, map);
	map_alocator(map);
	while (y < map->height)
	{
		row_loader(map, fd, y);
		y++;
	}
	close (fd);
}
