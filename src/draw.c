/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:28:43 by jlara-na          #+#    #+#             */
/*   Updated: 2023/12/14 20:14:27 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/FDF.h"

void	zoom_offset_start(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			fdf->map.points[x][y].x *= (int)fdf->cam.zoom;
			fdf->map.points[x][y].y *= (int)fdf->cam.zoom;
			fdf->map.points[x][y].x += (int)(WINDOW_C_X
					- (fdf->cam.zoom * (fdf->map.width / 2)));
			fdf->map.points[x][y].y += (int)(WINDOW_C_Y
					- (fdf->cam.zoom * (fdf->map.height / 2)));
			x++;
		}
		y++;
	}
}

void	scale(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			fdf->map.points[x][y].x *= fdf->cam.zoom;
			fdf->map.points[x][y].y *= fdf->cam.zoom;
			fdf->map.points[x][y].x += fdf->cam.x_offset;
			fdf->map.points[x][y].y += fdf->cam.y_offset;
			x++;
		}
		y++;
	}
}

void	rotate(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			fdf->map.points[x][y].x = (fdf->map.points[x][y].x - WINDOW_C_X)
				* cos(45 * M_PI / 180) - (fdf->map.points[x][y].y
					- WINDOW_C_Y) * sin(45 * M_PI / 180) + WINDOW_C_X;
			fdf->map.points[x][y].y = (fdf->map.points[x][y].x - WINDOW_C_X)
				* sin(45 * M_PI / 180) + (fdf->map.points[x][y].y
					- WINDOW_C_Y) * sin(45 * M_PI / 180) + WINDOW_C_Y;
			x++;
		}
		y++;
	}
}

void	apply_height(t_fdf *fdf, int sign)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width && sign > 0
				&& fdf->map.points[x][y].z < INT_MAX)
				fdf->map.points[x][y].y -= fdf->map.points[x][y].z;
			else
				fdf->map.points[x][y].y += fdf->map.points[x][y].z;
			x++;
		}
		y++;
	}
}

void	draw_map(t_fdf *fdf, int draw)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width - 1)
				bresenham_line(fdf, fdf->map.points[x][y],
					fdf->map.points[x + 1][y],
					(draw * fdf->map.points[x][y].c));
			if (y < fdf->map.height - 1)
				bresenham_line(fdf, fdf->map.points[x][y],
					fdf->map.points[x][y + 1],
					(draw * fdf->map.points[x][y].c));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img.img, 0, 0);
}
