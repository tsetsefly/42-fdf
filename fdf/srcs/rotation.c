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

	init_min_max(super_struct, 'x');
	i = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			super_struct->map[i][j].y = super_struct->map[i][j].y *
				cos(super_struct->angle_x) - super_struct->map[i][j].z *
				sin(super_struct->angle_x);
			super_struct->map[i][j].z = super_struct->map[i][j].y *
				sin(super_struct->angle_x) + super_struct->map[i][j].z *
				cos(super_struct->angle_x);
			check_min_max(super_struct, i, j, 'x');
			j++;
		}
		i++;
	}
}

void		y_axis(t_super *super_struct)
{
	int		i;
	int		j;

	// init_min_max(super_struct, 'x');
	i = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			super_struct->map[i][j].z = super_struct->map[i][j].z *
				cos(super_struct->angle_y) - super_struct->map[i][j].x *
				sin(super_struct->angle_y);
			super_struct->map[i][j].x = super_struct->map[i][j].z *
				sin(super_struct->angle_y) + super_struct->map[i][j].x *
				cos(super_struct->angle_y);
			// check_min_max(super_struct, i, j, 'x');
			j++;
		}
		i++;
	}
}

void		z_axis(t_super *super_struct)
{
	int		i;
	int		j;

	i = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			super_struct->map[i][j].x = super_struct->map[i][j].scaled_x *
				cos(super_struct->angle_z) - super_struct->map[i][j].scaled_y *
				sin(super_struct->angle_z);
			super_struct->map[i][j].y = super_struct->map[i][j].scaled_x *
				sin(super_struct->angle_z) + super_struct->map[i][j].scaled_y *
				cos(super_struct->angle_z);
			super_struct->map[i][j].z = super_struct->map[i][j].scaled_z;
			j++;
		}
		i++;
	}
}
