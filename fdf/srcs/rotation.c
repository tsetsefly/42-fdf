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

	i = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			super_struct->map[i][j].x = super_struct->map[i][j].scaled_x;
			super_struct->map[i][j].y =
				super_struct->map[i][j].scaled_y * cos(RADS(super_struct->angle_x))
				- super_struct->map[i][j].scaled_z * sin(RADS(super_struct->angle_x));
			super_struct->map[i][j].z =
				super_struct->map[i][j].scaled_y * sin(RADS(super_struct->angle_x))
				+ super_struct->map[i][j].scaled_z * cos(RADS(super_struct->angle_x));
			j++;
		}
		i++;
	}
}

void		y_axis(t_super *super_struct)
{
	int		i;
	int		j;
	double	temp;

	i = 0;
	temp = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			temp =
				super_struct->map[i][j].x * cos(RADS(super_struct->angle_y))
				- super_struct->map[i][j].z * sin(RADS(super_struct->angle_y));
			super_struct->map[i][j].z =
				super_struct->map[i][j].z * cos(RADS(super_struct->angle_y))
				+ super_struct->map[i][j].x * sin(RADS(super_struct->angle_y));
			super_struct->map[i][j].x = temp;
			j++;
		}
		i++;
	}
}

void		z_axis(t_super *super_struct)
{
	int		i;
	int		j;
	double	temp;

	init_min_max(super_struct);
	i = 0;
	temp = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			temp =
				super_struct->map[i][j].x * cos(RADS(super_struct->angle_z))
				- super_struct->map[i][j].y * sin(RADS(super_struct->angle_z));
			super_struct->map[i][j].y =
				super_struct->map[i][j].x * sin(RADS(super_struct->angle_z))
				+ super_struct->map[i][j].y * cos(RADS(super_struct->angle_z));
			super_struct->map[i][j].x = temp;
			check_min_max(super_struct, i, j);
			j++;
		}
		i++;
	}
}
