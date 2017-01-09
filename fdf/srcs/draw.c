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
		mlx_pixel_put(super_struct->mlx, super_struct->window, super_struct->x1
			, super_struct->y1, super_struct->color);
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
		mlx_pixel_put(super_struct->mlx, super_struct->window, super_struct->x1
			, super_struct->y1, super_struct->color);
		// printf("PIXEL: x = %f, y = %f, i = %f\n", x1, y1, i);
		super_struct->y1 += (RES * neg);
		super_struct->x1 = (super_struct->x1 == super_struct->x2) ?
			super_struct->x2 : ((super_struct->y1 - super_struct->y_int)
			/ super_struct->slope);
		k += RES;
	}
}

// void		draw_line(double x1, double y1, double x2, double y2, void *mlx, void *window, int color)
void		draw_line(int i, int j, t_super *super_struct, char letter)
{
	init_draw_vars(i, j, super_struct, letter);
	// printf("START: slope = %f,\ty-int = %f,\tx-int = %f,\tx2 - x1 = %f\n", slope, y_int, x_int, x2 - x1);
	if (fabs(super_struct->slope) < 1)
		low_slope(super_struct);
	else
		high_slope(super_struct);
}

void		connect_lines(t_super super_struct)
{
	int		i;
	int		j;

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
	mlx_key_hook(super_struct.window, input_detective, &super_struct);
	mlx_loop(super_struct.mlx);
}
