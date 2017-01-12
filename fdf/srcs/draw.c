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
		super_struct->mem_addr[(int)(round(super_struct->y1)
			* round(super_struct->max_x + 1) + round(super_struct->x1))]
			= super_struct->color;
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
		super_struct->mem_addr[(int)(round(super_struct->y1)
			* round(super_struct->max_x + 1) + round(super_struct->x1))]
			= super_struct->color;
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

void		connect_lines(t_super *super_struct)
{
	int		i;
	int		j;

	image_prep(super_struct);
	i = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			if (j < super_struct->cols - 1)
				draw_line(i, j, super_struct, 'j');
			if (i < super_struct->rows - 1)
				draw_line(i, j, super_struct, 'i');
			j++;
		}
		i++;
	}
	// center_points(&super_struct);
	mlx_put_image_to_window(super_struct->mlx, super_struct->window,
		super_struct->img, round((WINDOW_X - super_struct->max_x) / 2),
		round((WINDOW_Y - super_struct->max_y) / 2));
	mlx_key_hook(super_struct->window, input_detective, super_struct);
	mlx_loop(super_struct->mlx);
}
