/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjustments.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:32:24 by dtse              #+#    #+#             */
/*   Updated: 2017/01/05 16:32:25 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // REMOVE LATER!!!

void		subtract_min_points(t_super *super_struct)
{
	int		i;
	int		j;

	i = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			super_struct->map[i][j].x -= super_struct->min_x;
			super_struct->map[i][j].y -= super_struct->min_y;
			j++;
		}
		i++;
	}
}

// either adjust this and use it or remove later
void		center_points(t_super *super_struct)
{
	int		i;
	int		j;
	double	adjust_x;
	double	adjust_y;

	adjust_x = (WINDOW_X / 2) - (((super_struct->max_x - super_struct->min_x)
		/ 2) + super_struct->min_x);
	adjust_y = (WINDOW_Y / 2) - (((super_struct->max_y - super_struct->min_y)
		/ 2) + super_struct->min_y);
	// printf("adjust_x = %f, adjust_y = %f, center_x = %f, center_y = %f\n", adjust_x, adjust_y, (((super_struct->max_x - super_struct->min_x) / 2) + super_struct->min_x), (((super_struct->max_y - super_struct->min_y) / 2) + super_struct->min_y)); // REMOVE LATER
	i = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			super_struct->map[i][j].x += adjust_x;
			super_struct->map[i][j].y += adjust_y;
			j++;
		}
		i++;
	}
}

void		reset_points(t_super *super_struct)
{
	int		i;
	int		j;

	i = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			super_struct->map[i][j].x = super_struct->map[i][j].scaled_x;
			super_struct->map[i][j].y = super_struct->map[i][j].scaled_y;
			super_struct->map[i][j].z = super_struct->map[i][j].scaled_z;
			j++;
		}
		i++;
	}
	super_struct->angle_x = 0;
	super_struct->angle_y = 0;
	super_struct->angle_z = 0;
	connect_lines(super_struct);
}