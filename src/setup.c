/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:07:09 by jlara-na          #+#    #+#             */
/*   Updated: 2023/12/13 20:13:22 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/FDF.h"

static int	exists(const char *fname)
{
	int	fd;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		return (0);
	}
	close(fd);
	return (1);
}

static void	mlx_setup(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WINDOW_X, WINDOW_Y, "FDF by JLara-Na");
	mlx->img.img = mlx_new_image(mlx->mlx, WINDOW_X, WINDOW_Y);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bppx,
			&mlx->img.line_length, &mlx->img.endian);
}

static void	cam_setup(t_fdf *fdf)
{
	if (fdf->map.width - fdf->map.height > 0)
		fdf->cam.zoom = (WINDOW_Y - 25) / fdf->map.width;
	else
		fdf->cam.zoom = (WINDOW_Y - 25) / fdf->map.height;
	fdf->cam.x_offset = WINDOW_C_X - (fdf->cam.zoom * (fdf->map.width / 2));
	fdf->cam.y_offset = WINDOW_C_Y - (fdf->cam.zoom * (fdf->map.height / 2));
	fdf->cam.scale = 1;
}

static void	intro_image(t_fdf *fdf)
{
	if (exists("./resources/IntroImg.xpm") != 0)
	{
		fdf->mlx.img.img = mlx_xpm_file_to_image (fdf->mlx.mlx,
				"./resources/IntroImg.xpm", &fdf->intro.y, &fdf->intro.x);
		mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img.img,
			0, 0);
		fdf->intro.done = 0;
	}
	else
		terminate(ERROR_MISSING, &fdf->map);
}

void	fdf_setup(t_fdf *fdf, char *path)
{
	map_loader(&fdf->map, path);
	mlx_setup(&fdf->mlx);
	intro_image(fdf);
	cam_setup(fdf);
}
