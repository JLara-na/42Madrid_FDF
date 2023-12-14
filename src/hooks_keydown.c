/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_keydown.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 21:03:05 by jlara-na          #+#    #+#             */
/*   Updated: 2023/12/14 19:48:09 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/FDF.h"

int	hook_keydown_1(int key, t_fdf *fdf)
{
	if (key == KB_ESC)
		terminate(FDF_EXIT, &fdf->map);
	if (key == KB_ENTER && fdf->intro.done == 0)
	{
		set_start(fdf);
		fdf->intro.done = 1;
	}
	if (key == KB_UP && fdf->intro.done)
		movement(fdf, UP);
	if (key == KB_DOWN && fdf->intro.done)
		movement(fdf, DOWN);
	if (key == KB_RIGHT && fdf->intro.done)
		movement(fdf, RIGHT);
	if (key == KB_LEFT && fdf->intro.done)
		movement(fdf, LEFT);
	if (key == KB_W && fdf->intro.done)
		height(fdf, UP);
	if (key == KB_S && fdf->intro.done)
		height(fdf, DOWN);
	if (key == KB_E && fdf->cam.scale < 7 && fdf->intro.done)
		zoom(fdf, DOWN);
	if (key == KB_Q && fdf->cam.scale > 1 && fdf->intro.done)
		zoom(fdf, UP);
	return (0);
}

int	hook_exit(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.win);
	terminate(FDF_EXIT, &fdf->map);
	return (0);
}
