/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FDF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 19:26:20 by jlara-na          #+#    #+#             */
/*   Updated: 2023/12/14 19:48:13 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>
# include <errno.h>
# include "../lib/libft/libft.h"

//------------DEFINING VALUES------------//

# define X				0
# define Y				1
# define Z				2

# define DOWN			0
# define UP				1
# define RIGHT			2
# define LEFT			3

# define WINDOW_X		1920
# define WINDOW_Y		1080
# define WINDOW_C_X		960
# define WINDOW_C_Y		540
# define SLIDE_VALUE	250

//-----------------KEYS------------------//

# define KB_Q			12
# define KB_W			13
# define KB_E			14
# define KB_S			1
# define KB_DOWN		125
# define KB_UP			126
# define KB_RIGHT		124
# define KB_LEFT		123
# define KB_ESC			53
# define KB_ENTER		36

//----------------COLORS-----------------//

# define RED			0x00FF0000
# define GREEN			0x0000FF00 
# define BLUE			0x000000FF
# define MAGENTA		0x00FF00FF
# define YELLOW			0x00FFFF00
# define CYAN			0x0000FFFF
# define WHITE			0x00FFFFFF

# define PF_CLEAR		"\033[2J\033[1;1H"
# define PF_DEF_COLOR	"\033[0;39m"
# define PF_GRAY		"\033[0;90m"
# define PF_RED			"\033[0;91m"
# define PF_GREEN		"\033[0;92m"
# define PF_YELLOW		"\033[0;93m"
# define PF_YELLOWB		"\033[0;93;5m"
# define PF_BLUE		"\033[0;94m"
# define PF_MAGENTA		"\033[0;95m"
# define PF_CYAN		"\033[0;96m"
# define PF_WHITE		"\033[0;97m"

//----------------ERRORS-----------------//

# define ERROR_IAN		"\u274C\033[91m Invalid Argument Number\033[0;93m"
# define ERROR_MALLOC	"\u274C\033[91m Malloc ERROR\033[0;93m"
# define ERROR_IFD		"\u274C\033[91m Invalid FD\033[0;93m"
# define ERROR_IMEM		"\u274C\033[91m Invalid Map: \033[0;93mEmpty"
# define ERROR_IMDRS	"\u274C\033[91m Invalid Map: \033[0;93mInvalid Row Size"
# define ERROR_IMNL		"\u274C\033[91m Invalid Map: \033[0;93mNewLine at start"
# define ERROR_MISSING	"\u274C\033[91m Missing Files\033[0;93m"
# define FDF_EXIT		"\u2705\033[92m FDF Closed, See You Soon!\033[0;93m"

//----------DEFINING STRUCTURES----------//

typedef struct s_point {
	int	x;
	int	y;
	int	z;
	int	c;
}				t_point;

typedef struct s_bresenham {
	double	av;
	double	avt;
	double	avs;
	t_point	ap1;
	t_point	ap2;
	t_point	d;
	t_point	inct;
	t_point	incs;
}				t_bresenham;

typedef struct s_intro {
	int	x;
	int	y;
	int	done;
}				t_intro;

typedef struct s_cam {
	double	x_offset;
	double	y_offset;
	double	zoom;
	double	scale;
}				t_cam;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bppx;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_mlx {
	void	*mlx;
	void	*win;
	t_img	img;
}				t_mlx;

typedef struct s_map {
	t_point	**points;
	int		height;
	int		width;
}				t_map;

typedef struct s_fdf {
	t_map	map;
	t_mlx	mlx;
	t_cam	cam;
	t_intro	intro;
}				t_fdf;

//---------------FUNCTIONS---------------//

void	fdf_setup(t_fdf *fdf, char *path);
void	set_start(t_fdf *fdf);

//-------------MAP FUNCTIONS-------------//

void	map_loader(t_map *map, char *path);
void	x_mesure(t_map *map, char *row);
void	line_check(t_map *map, char *row);
void	point_loader(t_map *map, char **split, int y);
void	color_loader(t_map *map, char **split, int y);

//-------------EXIT FUNCTIONS------------//

void	terminate(char *s, t_map *map);

//-------------HOOK FUNCTIONS------------//

int		hook_keydown_1(int key, t_fdf *fdf);
int		hook_exit(t_fdf *fdf);
void	movement(t_fdf *fdf, int code);
void	height(t_fdf *fdf, int code);
void	zoom(t_fdf *fdf, int code);

//-------------MLX FUNCTIONS-------------//

void	pixel_put(t_img *img, int x_offset, int y_offset, int color);

//------------DRAW FUNCTIONS-------------//

void	bresenham_line(t_fdf *fdf, t_point p1, t_point p2, int draw);
void	draw_map(t_fdf *fdf, int draw);

//------------VALUE FUNCTIONS------------//

void	rotate(t_fdf *fdf);
void	scale(t_fdf *fdf);
void	apply_height(t_fdf *fdf, int sign);
void	zoom_offset_start(t_fdf *fdf);
void	move_x(t_fdf *fdf, int sign);
void	move_y(t_fdf *fdf, int sign);

#endif
