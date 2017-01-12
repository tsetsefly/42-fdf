/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   min_max_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 17:23:19 by dtse              #+#    #+#             */
/*   Updated: 2017/01/11 17:23:20 by dtse             ###   ########.fr       */
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

void		check_min_max(t_super *super_struct, int i, int j)
{
	if (super_struct->min_x > super_struct->map[i][j].x)
		super_struct->min_x = super_struct->map[i][j].x;
	if (super_struct->max_x < super_struct->map[i][j].x)
		super_struct->max_x = super_struct->map[i][j].x;
	if (super_struct->min_y > super_struct->map[i][j].y)
		super_struct->min_y = super_struct->map[i][j].y;
	if (super_struct->max_y < super_struct->map[i][j].y)
		super_struct->max_y = super_struct->map[i][j].y;
}

void		init_min_max(t_super *super_struct)
{
	super_struct->min_x = super_struct->map[0][0].x;
	super_struct->max_x = super_struct->min_x;
	super_struct->min_y = super_struct->map[0][0].y;
	super_struct->max_y = super_struct->min_y;
}

void		max_min_xy(t_super *super_struct)
{
	int		i;
	int		j;

	i = 0;
	init_min_max(super_struct);
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