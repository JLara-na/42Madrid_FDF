/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 17:50:48 by jlara-na          #+#    #+#             */
/*   Updated: 2023/12/11 19:50:39 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/FDF.h"

void	movement(t_fdf *fdf, int code)
{
	draw_map(fdf, 0);
	if (code <= 1)
		move_y(fdf, code);
	else
		move_x(fdf, code);
	draw_map(fdf, 1);
}

void	height(t_fdf *fdf, int code)
{
	draw_map(fdf, 0);
	apply_height(fdf, code);
	draw_map(fdf, 1);
}

static void	zoom_up_down(t_fdf *fdf, int code, int x, int y)
{
	if (code == UP)
	{
		fdf->map.points[x][y].x /= 2;
		fdf->map.points[x][y].y /= 2;
		fdf->map.points[x][y].x += WINDOW_C_X / 2;
		fdf->map.points[x][y].y += WINDOW_C_Y / 2;
	}
	if (code == DOWN)
	{
		fdf->map.points[x][y].x *= 2;
		fdf->map.points[x][y].y *= 2;
		fdf->map.points[x][y].x -= WINDOW_C_X;
		fdf->map.points[x][y].y -= WINDOW_C_Y;
	}
}

void	zoom(t_fdf *fdf, int code)
{
	int	x;
	int	y;

	y = 0;
	draw_map(fdf, 0);
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			zoom_up_down(fdf, code, x, y);
			x++;
		}
		y++;
	}
	if (code == UP)
		fdf->cam.scale--;
	if (code == DOWN)
		fdf->cam.scale++;
	draw_map(fdf, 1);
}
