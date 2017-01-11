/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   superstruct_setup.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:47:58 by dtse              #+#    #+#             */
/*   Updated: 2016/12/15 16:47:59 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // REMOVE LATER!!!

void		max_min_z(t_super *super_struct)
{
	int		i;
	int		j;

	i = 0;
	super_struct->max_z = super_struct->map[0][0].og_z;
	super_struct->min_z = super_struct->map[0][0].og_z;
	printf("BEFORE = MAX_Z = %f, MIN_Z = %f\n", super_struct->max_z, super_struct->min_z);
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			if (super_struct->map[i][j].og_z > super_struct->max_z)
				super_struct->max_z = super_struct->map[i][j].og_z;
			else if (super_struct->map[i][j].og_z < super_struct->min_z)
				super_struct->min_z = super_struct->map[i][j].og_z;
			j++;
		}
		i++;
	}
	super_struct->z_delta = super_struct->max_z - super_struct->min_z;
	printf("AFTER = MAX_Z = %f, MIN_Z = %f, Z_DELTA = %f\n", super_struct->max_z, super_struct->min_z, super_struct->z_delta);
}

void		scale_init_map(t_super *super_struct)
{
	int		i;
	int		j;
	double	x;
	double	y;


	y = 0;
	i = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		x = 0;
		while (j < super_struct->cols)
		{
			super_struct->map[i][j].scaled_x = x;
			super_struct->map[i][j].scaled_y = y;
			super_struct->map[i][j].scaled_z =
				super_struct->map[i][j].og_z * super_struct->step_unit / 2;
			super_struct->map[i][j].x = x;
			super_struct->map[i][j].y = y;
			super_struct->map[i][j].z = super_struct->map[i][j].scaled_z;
			x += super_struct->step_unit;
			j++;
		}
		y += super_struct->step_unit;
		i++;
	}
}

void		scale_that_shit(t_super *super_struct)
{
	if (super_struct->cols >= super_struct->rows && super_struct->cols
		>= super_struct->z_delta)
	{
		super_struct->step_unit = WINDOW_X * SCALE
			/ (super_struct->cols - 1);
		super_struct->long_axis = 'x';
	}
	else if (super_struct->rows >= super_struct->cols && super_struct->rows
		>= super_struct->z_delta)
	{
		super_struct->step_unit = WINDOW_Y * SCALE
			/ (super_struct->rows - 1);
		super_struct->long_axis = 'y';
	}
	else
	{
		super_struct->step_unit = ((WINDOW_X + WINDOW_Y) / 2)
			/ super_struct->z_delta;
		super_struct->long_axis = 'z';
	}
	super_struct->start_x = (WINDOW_X / 2) - (super_struct->step_unit
		* (super_struct->cols - 1) / 2);
	super_struct->start_y = (WINDOW_Y / 2) - (super_struct->step_unit
		* (super_struct->rows - 1) / 2);
	printf("step unit = %f, axis = %c, start_x = %f, start_y = %f\n", super_struct->step_unit, super_struct->long_axis, super_struct->start_x, super_struct->start_y);
	scale_init_map(super_struct);
	// print_shit(super_struct);
}

void		init_values(t_super *super_struct, char **av1)
{
	super_struct->file_name = *av1;
	super_struct->file_error = 0;
	super_struct->step_unit = 0;
	super_struct->angle_x = 0;
	super_struct->angle_y = 0;
	super_struct->angle_z = 0;
	super_struct->min_x = 0;
	super_struct->max_x = 0;
	super_struct->min_y = 0;
	super_struct->max_y = 0;
	super_struct->slope = 0;
	super_struct->color = 140 * 65536;
	super_struct->slope = 0;
	super_struct->y_int = 0;
	super_struct->x1 = 0;
	super_struct->x2 = 0;
	super_struct->y1 = 0;
	super_struct->y2 = 0;
	super_struct->z_delta = 0;
	super_struct->mlx = mlx_init();
	super_struct->window = mlx_new_window(super_struct->mlx, WINDOW_X, WINDOW_Y, "detective");
	super_struct->bits_per_pixel = 32;
	super_struct->endian = 0;
}

t_super		init_superstruct(char *av1)
{
	t_super	*super_struct;

	super_struct = (t_super *)malloc(sizeof(t_super));
	init_values(super_struct, &av1);
	file_detective(super_struct);
	if (super_struct->file_error)
		return(*super_struct);
	scale_that_shit(super_struct);
	return (*super_struct);
}