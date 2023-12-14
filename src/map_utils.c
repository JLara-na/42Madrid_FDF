/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:42:40 by jlara-na          #+#    #+#             */
/*   Updated: 2023/12/14 20:24:19 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/FDF.h"

void	x_mesure(t_map *map, char *row)
{
	int	i;

	i = 0;
	while (row[i++])
	{
		if (row[0] == '\n')
			terminate(ERROR_IMNL, map);
		if (row[i] == ' ' && row[i - 1] != ' ')
			map->width++;
		if (row[i] == '\0' && (row[i - 1] == '\n' || ft_isalnum(row[i - 1])))
			map->width++;
	}
}

void	line_check(t_map *map, char	*row)
{
	int	i;
	int	newwidth;

	i = 0;
	newwidth = 0;
	while (row[i++])
	{
		if (row[i] == '\0' && (row[i - 1] == '\n' || ft_isalnum(row[i - 1])))
			newwidth++;
		if (row[i] == ' ' && row[i - 1] != ' ')
			newwidth++;
	}
	if (map->width == newwidth)
		map->height++;
	else
		terminate(ERROR_IMDRS, map);
}

void	point_loader(t_map *map, char **split, int y)
{
	int	x;

	x = 0;
	while (split[x])
	{
		map->points[x][y].z = ft_atoi(&split[x][0]);
		map->points[x][y].x = x;
		map->points[x][y].y = y;
		x++;
	}
}

static int	str_hex_to_int(char **split, int x)
{
	int				result;
	int				y;

	y = -1;
	while (split[x][++y])
		split[x][y] = ft_toupper(split[x][y]);
	y = 0;
	while (split[x][y] != ',' && split[x][y] != '\0')
		y++;
	if (!split[x][y])
		return (0);
	y++;
	if (split[x][y] == '0')
		y++;
	if (split[x][y] == 'X')
		y++;
	result = ft_atoi_base(&split[x][y], "0123456789ABCDEF");
	return (result);
}

void	color_loader(t_map *map, char **split, int y)
{
	int	x;

	x = 0;
	while (split[x])
	{
		map->points[x][y].c = str_hex_to_int(split, x);
		if (!map->points[x][y].c)
			map->points[x][y].c = WHITE;
		x++;
	}
}
