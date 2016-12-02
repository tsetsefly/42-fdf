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

void		input_detective(int key_press, void *mlx)
{
	printf("key_press = %d\n", key_press);
	if (key_press == 53)
		exit(1);
	(void)mlx;
}

void		print_2D_chararray(char **array, int rows)
{
	int		i;
	size_t	len;
	
	i = 0;
	len = 0;
	ft_putstr("wahoo!\n");
	while (i < rows)
	{
		ft_putstr(array[i]);
		ft_putchar('\n');
		i++;
	}
}

void		file_detective(char *file_name)
{
	int		fd;
	int		rows;
	size_t	len;
	char	*line;
	char	**file_storage;

	// if ((fd = open("file", O_RDONLY)) == -1)
	// 	return (-1);

	// get dimensions of the array
	// malloc for array
	// fill array with values
	fd = open(file_name, O_RDONLY);
	rows = 0;
	len = 0;
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		rows++;
		free(line);
  	}
	printf("ROWS = %d\n", rows);
	close(fd);
	file_storage = (char **)malloc(sizeof(char *) * (rows + 1));
	fd = open(file_name, O_RDONLY);
	rows = 0;
  	while (get_next_line(fd, &line) > 0)
	{
		len = ft_strlen(line);
		printf("%s\tLEN = %lu\n", line, len);
		file_storage[rows] = (char *)malloc(sizeof(char) * (len + 1));
		ft_strcpy(file_storage[rows], line);
		// file_storage[rows][len + 1] = '\0';
		rows++;
		free(line);
  	}
  	file_storage[rows] = 0;
  	// print_2D_chararray(file_storage, rows);
}

void		test_print_spiral(void *mlx, void *window) // REMOVE LATER!!!
{
	int		color = 140 * 65536; // RGB = (R*65536)+(G*256)+B , (when R is RED, G is GREEN and B is BLUE)
	int 	color_change = 8;

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

int			main (int ac, char **av)
{
	void	*mlx;
	void	*window;
	int		window_x;
	int		window_y;
	

	if (ac == 2)
	{
		window_x = 800;
		window_y = 800;

		file_detective(av[1]);
		mlx = mlx_init();
		window = mlx_new_window(mlx, window_x, window_y, "detective");
		test_print_spiral(mlx, window);  // REMOVE LATER!!!
	}
	else
		printf("didn't pass a file!!!\n");
	return (0);
}