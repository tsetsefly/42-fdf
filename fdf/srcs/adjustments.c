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

void		check_min_max(t_super *super_struct, int i, int j, char letter)
{
	if (letter == 'x')
	{
		if (super_struct->min_x > super_struct->map[i][j].x)
			super_struct->min_x = super_struct->map[i][j].x;
		if (super_struct->max_x < super_struct->map[i][j].x)
			super_struct->max_x = super_struct->map[i][j].x;
	}
	if (letter == 'x')
	{
		if (super_struct->min_y > super_struct->map[i][j].y)
			super_struct->min_y = super_struct->map[i][j].y;
		if (super_struct->max_y < super_struct->map[i][j].y)
			super_struct->max_y = super_struct->map[i][j].y;
	}
}

void		init_min_max(t_super *super_struct, char letter)
{
	if (letter == 'x')
	{
		super_struct->min_x = super_struct->map[0][0].x;
		super_struct->max_x = super_struct->min_x;	
	}
	if (letter == 'x')
	{
		super_struct->min_y = super_struct->map[0][0].y * cos(super_struct->angle_x)
			- super_struct->map[0][0].z * sin(super_struct->angle_x);
		super_struct->max_y = super_struct->min_y;	
	} 
}

void		center_points(t_super *super_struct)
{
	int		i;
	int		j;
	double	center_x;
	double	center_y;
	double	adjust_x;
	double	adjust_y;

	center_x = ((super_struct->max_x - super_struct->min_x) / 2)
		+ super_struct->min_x;
	center_y = ((super_struct->max_y - super_struct->min_y) / 2)
		+ super_struct->min_y;
	adjust_x = (WINDOW_X / 2) - center_x;
	adjust_y = (WINDOW_Y / 2) - center_y;
	printf("adjust_x = %f, adjust_y = %f, center_x = %f, center_y = %f\n", adjust_x, adjust_y, center_x, center_y); // REMOVE LATER!!! //
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
	connect_lines(*super_struct);
}