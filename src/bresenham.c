/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlara-na <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 22:19:43 by jlara-na          #+#    #+#             */
/*   Updated: 2023/12/14 18:12:21 by jlara-na         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/FDF.h"

static void	increase_tilted(t_point *d, t_point *inct)
{
	if (d->y >= 0)
		inct->y = 1;
	else
	{
		d->y = -(d->y);
		inct->y = -1;
	}
	if (d->x >= 0)
		inct->x = 1;
	else
	{
		d->x = -(d->x);
		inct->x = -1;
	}
}

static void	increase_straight(t_point *d, t_point *inct, t_point *incs)
{
	int	k;

	if (d->x >= d->y)
	{
		incs->y = 0;
		incs->x = inct->x;
	}
	else
	{
		incs->x = 0;
		incs->y = inct->y;
		k = d->x;
		d->x = d->y;
		d->y = k;
	}
}

static void	draw_line(t_fdf *fdf, t_bresenham *l, int draw)
{
	while (l->ap1.x != l->ap2.x)
	{
		pixel_put(&fdf->mlx.img, l->ap1.x, l->ap1.y, draw);
		if (l->av >= 0)
		{
			l->ap1.x += l->inct.x;
			l->ap1.y += l->inct.y;
			l->av += l->avt;
		}
		else
		{
			l->ap1.x += l->incs.x;
			l->ap1.y += l->incs.y;
			l->av += l->avs;
		}
	}
}

void	bresenham_line(t_fdf *fdf, t_point p1, t_point p2, int draw)
{
	t_bresenham	l;

	l.ap1 = p1;
	l.ap2 = p2;
	l.d.x = p2.x - p1.x;
	l.d.y = p2.y - p1.y;
	increase_tilted(&l.d, &l.inct);
	increase_straight(&l.d, &l.inct, &l.incs);
	l.avs = 2 * l.d.y;
	l.av = l.avs - l.d.x;
	l.avt = l.av - l.d.x;
	draw_line(fdf, &l, draw);
}
