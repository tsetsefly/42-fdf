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

void		ft_swap_doubles(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void		draw_line(double x1, double y1, double x2, double y2, void *mlx, void *window, int color)
{
	double	i;
	double	slope;
	double	y_int;
	// double	x_int;
	double	max;
	double	res;
	int		neg;

	// mlx_pixel_put(mlx, window, x1, y1, color);
	// mlx_pixel_put(mlx, window, x2, y2, color);

	slope = (y2 - y1) / (x2 - x1);
	y_int = y1 - slope * x1;
	// x_int = (y_int * -1) / slope;
	// printf("START: slope = %f,\ty-int = %f,\tx-int = %f,\tx2 - x1 = %f\n", slope, y_int, x_int, x2 - x1);
	i = 0;
	res = (0.5);
	// max = (fabs(x2 - x1) > fabs(y2 - y1)) ? fabs(x2 - x1) : fabs(y2 - y1);
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

void		input_detective(int key_press, void *mlx)
{
	printf("key_press = %d\n", key_press);
	if (key_press == 53)
		exit(1);
	(void)mlx;
}

void		file_detective(char *file_name)
{
	int		fd;
	char	*line;

	// if ((fd = open("file", O_RDONLY)) == -1)
	// 	return (-1);
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd, &line) != 0)
	{
		printf("%s\n", line);
		free(line);
  	}
	close(fd);
}

int			main (int ac, char **av)
{
	void	*mlx;
	void	*window;
	int		window_x;
	int		window_y;
	int		color;
	int 	color_change = 8;

	if (ac == 2)
	{
		window_x = 800;
		window_y = 800;
		color = 140 * 65536; // RGB = (R*65536)+(G*256)+B , (when R is RED, G is GREEN and B is BLUE)

		file_detective(av[1]);

		mlx = mlx_init();
		window = mlx_new_window(mlx, window_x, window_y, "detective");
		// draw_line(400, 400, 200, 200, mlx, window, color);
		// draw_line(400, 400, 600, 200, mlx, window, color);
		// draw_line(400, 400, 600, 600, mlx, window, color);
		// draw_line(400, 400, 600, 800, mlx, window, color);
		// draw_line(400, 400, 600, 0, mlx, window, color);

		// draw_line(200, 200, 400, 400, mlx, window, color);
		// draw_line(600, 200, 400, 400, mlx, window, color);
		// draw_line(600, 600, 400, 400, mlx, window, color);
		// draw_line(200, 600, 400, 400, mlx, window, color);

		// VERTICAL LINE UP --> DOWN HERE
		draw_line(400, 200, 400, 400, mlx, window, color += color_change);

		draw_line(450, 200, 400, 400, mlx, window, color += color_change);
		draw_line(500, 200, 400, 400, mlx, window, color += color_change);
		draw_line(550, 200, 400, 400, mlx, window, color += color_change);
		
		draw_line(600, 200, 400, 400, mlx, window, color += color_change);
		
		draw_line(600, 250, 400, 400, mlx, window, color += color_change);
		draw_line(600, 300, 400, 400, mlx, window, color += color_change);
		draw_line(600, 350, 400, 400, mlx, window, color += color_change);
		
		draw_line(600, 400, 400, 400, mlx, window, color += color_change);
		
		draw_line(600, 450, 400, 400, mlx, window, color += color_change);
		draw_line(600, 500, 400, 400, mlx, window, color += color_change);
		draw_line(600, 550, 400, 400, mlx, window, color += color_change);
		
		draw_line(600, 600, 400, 400, mlx, window, color += color_change);

		draw_line(550, 600, 400, 400, mlx, window, color += color_change);
		draw_line(500, 600, 400, 400, mlx, window, color += color_change);
		draw_line(450, 600, 400, 400, mlx, window, color += color_change);

		// VERTICAL LINE DOWN --> UP HERE
		draw_line(400, 600, 400, 400, mlx, window, color += color_change);

		draw_line(350, 600, 400, 400, mlx, window, color += color_change);
		draw_line(300, 600, 400, 400, mlx, window, color += color_change);
		draw_line(250, 600, 400, 400, mlx, window, color += color_change);

		draw_line(200, 600, 400, 400, mlx, window, color += color_change);

		draw_line(200, 550, 400, 400, mlx, window, color += color_change);
		draw_line(200, 500, 400, 400, mlx, window, color += color_change);
		draw_line(200, 450, 400, 400, mlx, window, color += color_change);

		draw_line(200, 400, 400, 400, mlx, window, color += color_change);

		draw_line(200, 350, 400, 400, mlx, window, color += color_change);
		draw_line(200, 300, 400, 400, mlx, window, color += color_change);
		draw_line(200, 250, 400, 400, mlx, window, color += color_change);

		draw_line(200, 200, 400, 400, mlx, window, color += color_change);

		draw_line(250, 200, 400, 400, mlx, window, color += color_change);
		draw_line(300, 200, 400, 400, mlx, window, color += color_change);
		draw_line(350, 200, 400, 400, mlx, window, color += color_change);

		mlx_key_hook(window, (void *)input_detective, mlx);
		mlx_loop(mlx);
	}
	else
		printf("wahoo!!!\n");
	return (0);
}