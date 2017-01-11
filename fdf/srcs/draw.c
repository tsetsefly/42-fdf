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

void		init_draw_vars(int i, int j, t_super *super_struct, char letter)
{
	super_struct->x1 = super_struct->map[i][j].x;
	super_struct->y1 = super_struct->map[i][j].y;
	if (letter == 'j')
	{
		super_struct->x2 = super_struct->map[i][j + 1].x;
		super_struct->y2 = super_struct->map[i][j + 1].y;
	}
	else if (letter == 'i')
	{
		super_struct->x2 = super_struct->map[i + 1][j].x;
		super_struct->y2 = super_struct->map[i + 1][j].y;
	}
	super_struct->slope = (super_struct->y2 - super_struct->y1)
		/ (super_struct->x2 - super_struct->x1);
	super_struct->y_int = super_struct->y1
		- super_struct->slope * super_struct->x1;
}

void		low_slope(t_super *super_struct)
{
	double	k;
	double	max;
	int		neg;

	k = 0;
	max = fabs(super_struct->x2 - super_struct->x1);
	neg = (super_struct->x2 < super_struct->x1) ? -1 : 1;
	while (k <= max)
	{
		// mlx_pixel_put(super_struct->mlx, super_struct->window, super_struct->x1
		// 	, super_struct->y1, super_struct->color);
		super_struct->mem_addr[(int)(round(super_struct->y1) * round(super_struct->max_x + 1) + round(super_struct->x1))] = super_struct->color;
		// printf("PIXEL: x = %f, y = %f, i = %f\n", x1, y1, i);
		super_struct->x1 += (RES * neg);
		super_struct->y1 = super_struct->slope * super_struct->x1
			+ super_struct->y_int;
		k += RES;
	}
}

void		high_slope(t_super *super_struct)
{
	double	k;
	double	max;
	int		neg;

	k = 0;
	max = fabs(super_struct->y2 - super_struct->y1);
	neg = (super_struct->y2 < super_struct->y1) ? -1 : 1;
	while (k <= max)
	{
		// mlx_pixel_put(super_struct->mlx, super_struct->window, super_struct->x1
		// 	, super_struct->y1, super_struct->color);
		super_struct->mem_addr[(int)(round(super_struct->y1) * round(super_struct->max_x + 1) + round(super_struct->x1))] = super_struct->color;
		// printf("PIXEL: x = %f, y = %f, i = %f\n", x1, y1, i);
		super_struct->y1 += (RES * neg);
		super_struct->x1 = (super_struct->x1 == super_struct->x2) ?
			super_struct->x2 : ((super_struct->y1 - super_struct->y_int)
			/ super_struct->slope);
		k += RES;
	}
}

void		draw_line(int i, int j, t_super *super_struct, char letter)
{
	init_draw_vars(i, j, super_struct, letter);
	// printf("START: slope = %f,\ty-int = %f,\tx-int = %f,\tx2 - x1 = %f\n", slope, y_int, x_int, x2 - x1);
	if (fabs(super_struct->slope) < 1)
		low_slope(super_struct);
	else
		high_slope(super_struct);
}

void		max_min_xy(t_super *super_struct)
{
	int		i;
	int		j;

	i = 0;
	init_min_max(super_struct, 'z');
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			check_min_max(super_struct, i, j);
			j++;
		}
		i++;
	}
}

void		connect_lines(t_super super_struct)
{
	int		i;
	int		j;

	printf("BEFORE = min_x = %f, max_x = %f, min_y = %f, max_y = %f\n", super_struct.min_x, super_struct.max_x, super_struct.min_y, super_struct.max_y);
	max_min_xy(&super_struct);
	subtract_min_points(&super_struct);
	max_min_xy(&super_struct);
	printf("AFTER = min_x = %f, max_x = %f, min_y = %f, max_y = %f\n", super_struct.min_x, super_struct.max_x, super_struct.min_y, super_struct.max_y);
	super_struct.size_line = (round(super_struct.max_x) + 1) * 4;
	super_struct.img = mlx_new_image(super_struct.mlx, round(super_struct.max_x + 1), round(super_struct.max_y) + 1);
	super_struct.mem_addr = (unsigned int *)mlx_get_data_addr(super_struct.img, &super_struct.bits_per_pixel, &super_struct.size_line, &super_struct.endian);
	printf("GOT HERE!!!!\n");
	i = 0;
	while (i < super_struct.rows)
	{
		j = 0;
		while (j < super_struct.cols)
		{
			if (j < super_struct.cols - 1)
				draw_line(i, j, &super_struct, 'j');
			if (i < super_struct.rows - 1)
				draw_line(i, j, &super_struct, 'i');
			j++;
		}
		i++;
	}
	// center_points(&super_struct);
	// round((WINDOW_X / 2) - (super_struct.max_x / 2))
	mlx_put_image_to_window(super_struct.mlx, super_struct.window, super_struct.img, round((WINDOW_X - super_struct.max_x) / 2), round((WINDOW_Y - super_struct.max_y) / 2));
	mlx_key_hook(super_struct.window, input_detective, &super_struct);
	mlx_loop(super_struct.mlx);
}
