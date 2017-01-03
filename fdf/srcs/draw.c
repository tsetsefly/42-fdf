/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 17:15:35 by dtse              #+#    #+#             */
/*   Updated: 2016/12/15 17:15:37 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // REMOVE LATER!!!

// need to make this fit norm
// can also make fit with superstruct, or some other struct
void		draw_line(double x1, double y1, double x2, double y2, void *mlx, void *window, int color)
{
	double	i;
	double	slope;
	double	y_int;
	double	max;
	double	res;
	int		neg;

	slope = (y2 - y1) / (x2 - x1);
	y_int = y1 - slope * x1;
	// printf("START: slope = %f,\ty-int = %f,\tx-int = %f,\tx2 - x1 = %f\n", slope, y_int, x_int, x2 - x1);
	i = 0;
	res = (0.5);
	if (fabs(slope) < 1)
	{
		max = fabs(x2 - x1);
		neg = (x2 < x1) ? -1 : 1;
		while (i <= max)
		{
			mlx_pixel_put(mlx, window, x1, y1, color);
			// printf("PIXEL: x = %f, y = %f, i = %f\n", x1, y1, i);
			x1 += (res * neg);
			y1 = slope * x1 + y_int;
			i += res;
		}
	}
	else
	{
		max = fabs(y2 - y1);
		neg = (y2 < y1) ? -1 : 1;
		while (i <= max)
		{
			mlx_pixel_put(mlx, window, x1, y1, color);
			// printf("PIXEL: x = %f, y = %f, i = %f\n", x1, y1, i);
			y1 += (res * neg);
			x1 = (x1 == x2) ? x2 : ((y1 - y_int) / slope);
			i += res;
		}
	}	
}

// void		draw_line(double x1, double y1, double x2, double y2, void *mlx, void *window, int color)
void		connect_lines(t_super super_struct)
{
	int		i;
	int		j;
	int		color = 140 * 65536;

	i = 0;
	while (i < super_struct.rows)
	{
		j = 0;
		while (j < super_struct.cols)
		{
			if (j < super_struct.cols - 1)
				draw_line(super_struct.map[i][j].x, super_struct.map[i][j].y, super_struct.map[i][j + 1].x,
					super_struct.map[i][j + 1].y, super_struct.mlx, super_struct.window, color);
			if (i < super_struct.rows - 1)
				draw_line(super_struct.map[i][j].x, super_struct.map[i][j].y, super_struct.map[i + 1][j].x,
					super_struct.map[i + 1][j].y, super_struct.mlx, super_struct.window, color);
			j++;
		}
		i++;
	}
	mlx_key_hook(super_struct.window, input_detective, &super_struct);
	mlx_loop(super_struct.mlx);
}
