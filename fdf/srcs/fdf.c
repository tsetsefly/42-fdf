/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 17:40:18 by dtse              #+#    #+#             */
/*   Updated: 2016/11/15 17:40:19 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // REMOVE LATER!!!!

void		draw_line(double x1, double y1, double x2, double y2, void *mlx, void *window, int color)
{
	double	i;
	double	slope;
	double	y_int;
	double	max;
	double	res;
	int		neg;

	// mlx_pixel_put(mlx, window, x1, y1, color);
	// mlx_pixel_put(mlx, window, x2, y2, color);
	slope = (y2 - y1) / (x2 - x1);
	y_int = y1 - slope * x1;
	// printf("START: slope = %f, y-int = %f, x2 - x1 = %f\n", slope, y_int, x2 - x1);
	i = 0;
	res = (0.5);
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

int			main ()
{
	void	*mlx;
	void	*window;
	int		window_x;
	int		window_y;
	int		color;

	window_x = 500;
	window_y = 1000;
	color = 255 * 65536; // RGB = (R*65536)+(G*256)+B , (when R is RED, G is GREEN and B is BLUE)

	mlx = mlx_init();
	window = mlx_new_window(mlx, window_x, window_y, "detective");
	mlx_string_put(mlx, window, 250, 500, color, "detective");
	draw_line(200, 200, 400, 400, mlx, window, color);
	mlx_loop(mlx);

	printf("wahoo!!!\n");
	return (0);
}