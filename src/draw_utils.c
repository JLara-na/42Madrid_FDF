/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:21:10 by jlara-na          #+#    #+#             */
/*   Updated: 2023/12/14 18:12:44 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/FDF.h"

void	pixel_put(t_img *img, int x_offset, int y_offset, int color)
{
	char	*dst;

	if (x_offset < 0 || x_offset >= 1920 || y_offset < 0 || y_offset >= 1080)
		return ;
	dst = img->addr + (y_offset * img->line_length + x_offset
			* (img->bppx / 8));
	*(unsigned int *)dst = color;
}

void	intro_image(t_fdf *fdf)
{
	fdf->mlx.img.img = mlx_xpm_file_to_image (fdf->mlx.mlx,
			"./resources/IntroImg.xpm", &fdf->intro.y, &fdf->intro.x);
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img.img, 0, 0);
	fdf->intro.done = 0;
}

void	move_y(t_fdf *fdf, int sign)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width && sign == 0)
				fdf->map.points[x][y].y -= SLIDE_VALUE;
			else
				fdf->map.points[x][y].y += SLIDE_VALUE;
			x++;
		}
		y++;
	}
}

void	move_x(t_fdf *fdf, int sign)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map.height)
	{
		x = 0;
		while (x < fdf->map.width)
		{
			if (x < fdf->map.width && sign == 2)
				fdf->map.points[x][y].x -= SLIDE_VALUE;
			else
				fdf->map.points[x][y].x += SLIDE_VALUE;
			x++;
		}
		y++;
	}
}

void	set_start(t_fdf *fdf)
{
	fdf->mlx.img.img = mlx_new_image(fdf->mlx.mlx, WINDOW_X, WINDOW_Y);
	fdf->mlx.img.addr = mlx_get_data_addr(fdf->mlx.img.img, &fdf->mlx.img.bppx,
			&fdf->mlx.img.line_length, &fdf->mlx.img.endian);
	scale(fdf);
	rotate(fdf);
	apply_height(fdf, 1);
	draw_map(fdf, 1);
}
