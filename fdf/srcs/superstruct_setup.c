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

// can probably merge this in later to something like the scaling
t_super		max_min_z(t_super super_struct)
{
	int		i;
	int		j;

	i = 0;
	super_struct.max_z = super_struct.map[0][0].og_z;
	super_struct.min_z = super_struct.map[0][0].og_z;
	printf("MAX_Z = %f, MIN_Z = %f\n", super_struct.max_z, super_struct.min_z);
	while (i < super_struct.rows)
	{
		j = 0;
		while (j < super_struct.cols)
		{
			// printf("(%d, %d) %f\t", i, j, super_struct.map[i][j].og_z);
			if (super_struct.map[i][j].og_z > super_struct.max_z)
			{
				super_struct.max_z = super_struct.map[i][j].og_z;
				// printf("MAX_Z = %f, MIN_Z = %f\n", super_struct.max_z, super_struct.min_z);
			}
			else if (super_struct.map[i][j].og_z < super_struct.min_z)
			{
				super_struct.min_z = super_struct.map[i][j].og_z;
				// printf("MAX_Z = %f, MIN_Z = %f\n", super_struct.max_z, super_struct.min_z);
			}
			j++;
		}
		i++;
	}
	printf("MAX_Z = %f, MIN_Z = %f\n", super_struct.max_z, super_struct.min_z);
	return (super_struct);
}

t_super		scale_init_map(t_super super_struct)
{
	int		i;
	int		j;
	double	x;
	double	y;

	y = super_struct.start_y;
	i = 0;
	while (i < super_struct.rows)
	{
		j = 0;
		x = super_struct.start_x;
		while (j < super_struct.cols)
		{
			super_struct.map[i][j].scaled_x = x;
			super_struct.map[i][j].scaled_y = y;
			super_struct.map[i][j].scaled_z = super_struct.map[i][j].og_z * super_struct.step_unit / 2;
			super_struct.map[i][j].x = x;
			super_struct.map[i][j].y = y;
			super_struct.map[i][j].z = super_struct.map[i][j].scaled_z;
			x += super_struct.step_unit;
			j++;
		}
		y += super_struct.step_unit;
		i++;
	}
	return (super_struct);
}

t_super		scale_that_shit(t_super super_struct)
{
	super_struct.step_unit = 0;

	// not quite centered
	if (super_struct.cols >= super_struct.rows)
	{
		super_struct.step_unit = ((3 * WINDOW_X) / 5) / (super_struct.cols + 1);
		super_struct.long_axis = 'x';
	}
	else
	{
		super_struct.step_unit = ((3 * WINDOW_Y) / 5) / (super_struct.rows + 1);
		super_struct.long_axis = 'y';
	}
	super_struct.start_x = (WINDOW_X / 2) - (super_struct.step_unit * (super_struct.cols) / 2);
	super_struct.start_y = (WINDOW_Y / 2) - (super_struct.step_unit * (super_struct.rows) / 2);
	printf("step unit = %f, axis = %c, start_x = %f, start_y = %f\n", super_struct.step_unit, super_struct.long_axis, super_struct.start_x, super_struct.start_y);
	super_struct = scale_init_map(super_struct);
	// print_shit(super_struct);
	return (super_struct);
}

void		init_values(t_super *super_struct)
{
	printf("wahoo!");
	(void)super_struct;
}

t_super		init_superstruct(char *av1)
{
	t_super	super_struct;

	// can make this more efficient with pointers instead of copying variables through functions
	super_struct.angle_x = 0;
	super_struct.angle_y = 0;
	super_struct.angle_z = 0;
	init_values(&super_struct);
	super_struct.file_name = av1;
	super_struct = file_detective(super_struct);
	super_struct.mlx = mlx_init();
	super_struct.window = mlx_new_window(super_struct.mlx, WINDOW_X, WINDOW_Y, "detective");
	super_struct = scale_that_shit(super_struct);
	return (super_struct);
}