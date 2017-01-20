/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_support.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 19:33:00 by dtse              #+#    #+#             */
/*   Updated: 2017/01/10 19:33:02 by dtse             ###   ########.fr       */
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

void		image_prep(t_super *super_struct)
{
	// printf("BEFORE = min_x = %f, max_x = %f, min_y = %f, max_y = %f\n", super_struct->min_x, super_struct->max_x, super_struct->min_y, super_struct->max_y);
	max_min_xy(super_struct);
	subtract_min_points(super_struct);
	max_min_xy(super_struct);
	// printf("AFTER = min_x = %f, max_x = %f, min_y = %f, max_y = %f\n", super_struct->min_x, super_struct->max_x, super_struct->min_y, super_struct->max_y);
	super_struct->size_line = (round(super_struct->max_x) + 1) * 4;
	super_struct->img = mlx_new_image(super_struct->mlx,
		round(super_struct->max_x + 1), round(super_struct->max_y) + 1);
	super_struct->mem_addr = (unsigned int *)mlx_get_data_addr(super_struct->img
		, &super_struct->bits_per_pixel, &super_struct->size_line,
		&super_struct->endian);
	// printf("GOT HERE!!!!\n");
}
