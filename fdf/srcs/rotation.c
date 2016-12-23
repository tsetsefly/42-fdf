/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:35:09 by dtse              #+#    #+#             */
/*   Updated: 2016/12/15 16:35:13 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // REMOVE LATER!!!!

void		x_axis(t_super *super_struct)
{
	int		i;
	int		j;

	// need to update the angle based on key press
	// need to apply the axis equation to each point in the map
	// radians = degrees * pi / 180
	// need to translate from neutral position each time? in that case need to sequentially run against x, y, z
	super_struct->angle_x += X_ROT * M_PI / 180.0;
	printf("angle_x = %f\n", super_struct->angle_x);
	i = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			// z-axis
			// super_struct->map[i][j].x = super_struct->map[i][j].scaled_x * cos(super_struct->angle_x) - super_struct->map[i][j].scaled_y * sin(super_struct->angle_x);
			// super_struct->map[i][j].y = super_struct->map[i][j].scaled_x * sin(super_struct->angle_x) + super_struct->map[i][j].scaled_y * cos(super_struct->angle_x);
			// super_struct->map[i][j].z = super_struct->map[i][j].scaled_z;

			// x-axis
			super_struct->map[i][j].y = super_struct->map[i][j].scaled_y * cos(super_struct->angle_x) - super_struct->map[i][j].scaled_z * sin(super_struct->angle_x);
			super_struct->map[i][j].z = super_struct->map[i][j].scaled_y * sin(super_struct->angle_x) + super_struct->map[i][j].scaled_z * cos(super_struct->angle_x);
			super_struct->map[i][j].x = super_struct->map[i][j].scaled_x;
			j++;
		}
		i++;
	}
	connect_lines(*super_struct);
}

void		y_axis(t_super *super_struct)
{
	int		i;
	int		j;

	super_struct->angle_y += X_ROT * M_PI / 180.0;
	printf("angle_y = %f\n", super_struct->angle_y);
	i = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			super_struct->map[i][j].z = super_struct->map[i][j].scaled_y * cos(super_struct->angle_y) - super_struct->map[i][j].scaled_x * cos(super_struct->angle_y);
			super_struct->map[i][j].x = super_struct->map[i][j].scaled_z * sin(super_struct->angle_y) + super_struct->map[i][j].scaled_x * cos(super_struct->angle_y);
			super_struct->map[i][j].y = super_struct->map[i][j].scaled_y;
			j++;
		}
		i++;
	}
	connect_lines(*super_struct);
}