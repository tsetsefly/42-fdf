/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_functions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:54:51 by dtse              #+#    #+#             */
/*   Updated: 2016/12/15 16:54:52 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // REMOVE LATER!!!

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

void		print_map(t_super super_struct)
{
	int i;
	int j;

	i = 0;
	while (i < super_struct.rows)
	{
		j = 0;
		while (j < super_struct.cols)
		{
			printf("(%d,%d) %d \t", (int)super_struct.map[i][j].og_x, (int)super_struct.map[i][j].og_y, (int)super_struct.map[i][j].og_z);
			j++;
		}
		printf("\n");
		i++;
	}
}

void		print_shit(t_super super_struct)
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
			mlx_pixel_put(super_struct.mlx, super_struct.window, super_struct.map[i][j].scaled_x, super_struct.map[i][j].scaled_y, color);
			j++;
		}
		i++;
	}
	mlx_key_hook(super_struct.window, input_detective, &super_struct);
	mlx_loop(super_struct.mlx);
}

// void		test_print_spiral(void *mlx, void *window) // REMOVE LATER!!!
// {
// 	int		color = 140 * 65536; // RGB = (R*65536)+(G*256)+B , (when R is RED, G is GREEN and B is BLUE)
// 	int 	color_change = 8;

// 	// VERTICAL LINE UP --> DOWN HERE
// 	draw_line(400, 200, 400, 400, mlx, window, color += color_change);

// 	draw_line(450, 200, 400, 400, mlx, window, color += color_change);
// 	draw_line(500, 200, 400, 400, mlx, window, color += color_change);
// 	draw_line(550, 200, 400, 400, mlx, window, color += color_change);
	
// 	draw_line(600, 200, 400, 400, mlx, window, color += color_change);
	
// 	draw_line(600, 250, 400, 400, mlx, window, color += color_change);
// 	draw_line(600, 300, 400, 400, mlx, window, color += color_change);
// 	draw_line(600, 350, 400, 400, mlx, window, color += color_change);
	
// 	draw_line(600, 400, 400, 400, mlx, window, color += color_change);
	
// 	draw_line(600, 450, 400, 400, mlx, window, color += color_change);
// 	draw_line(600, 500, 400, 400, mlx, window, color += color_change);
// 	draw_line(600, 550, 400, 400, mlx, window, color += color_change);
	
// 	draw_line(600, 600, 400, 400, mlx, window, color += color_change);

// 	draw_line(550, 600, 400, 400, mlx, window, color += color_change);
// 	draw_line(500, 600, 400, 400, mlx, window, color += color_change);
// 	draw_line(450, 600, 400, 400, mlx, window, color += color_change);

// 	// VERTICAL LINE DOWN --> UP HERE
// 	draw_line(400, 600, 400, 400, mlx, window, color += color_change);

// 	draw_line(350, 600, 400, 400, mlx, window, color += color_change);
// 	draw_line(300, 600, 400, 400, mlx, window, color += color_change);
// 	draw_line(250, 600, 400, 400, mlx, window, color += color_change);

// 	draw_line(200, 600, 400, 400, mlx, window, color += color_change);

// 	draw_line(200, 550, 400, 400, mlx, window, color += color_change);
// 	draw_line(200, 500, 400, 400, mlx, window, color += color_change);
// 	draw_line(200, 450, 400, 400, mlx, window, color += color_change);

// 	draw_line(200, 400, 400, 400, mlx, window, color += color_change);

// 	draw_line(200, 350, 400, 400, mlx, window, color += color_change);
// 	draw_line(200, 300, 400, 400, mlx, window, color += color_change);
// 	draw_line(200, 250, 400, 400, mlx, window, color += color_change);

// 	draw_line(200, 200, 400, 400, mlx, window, color += color_change);

// 	draw_line(250, 200, 400, 400, mlx, window, color += color_change);
// 	draw_line(300, 200, 400, 400, mlx, window, color += color_change);
// 	draw_line(350, 200, 400, 400, mlx, window, color += color_change);

// 	mlx_key_hook(window, (void *)input_detective, mlx);
// 	mlx_loop(mlx);
// }
