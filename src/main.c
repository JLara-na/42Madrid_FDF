/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 19:50:50 by jlara-na          #+#    #+#             */
/*   Updated: 2023/12/14 20:30:09 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/FDF.h"

/*static void	leak(void)
{
	system("leaks -q fdf");
}*/

void	terminate(char *s, t_map *map)
{
	int	x;

	x = -1;
	if (map->height && map->width && (s != ERROR_IMDRS || s != ERROR_IMNL))
	{
		while (x++ < map->width)
			free(map->points[x]);
		free(map->points);
	}
	ft_putendl_fd(PF_CLEAR, 1);
	if (s == FDF_EXIT)
		ft_putendl_fd(s, 1);
	else
	{
		if (!errno)
			ft_putendl_fd(s, 2);
		else
			perror(s);
	}
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	char	*path;

	if (argc == 2 && argv[1])
	{
		path = argv[1];
		fdf_setup(&fdf, path);
		mlx_key_hook(fdf.mlx.win, hook_keydown_1, &fdf);
		mlx_hook(fdf.mlx.win, 17, 0, hook_exit, &fdf);
		mlx_loop(&fdf.mlx);
	}
	else
		terminate(ERROR_IAN, &fdf.map);
}
