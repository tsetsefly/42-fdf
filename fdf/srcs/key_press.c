/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 23:42:18 by dtse              #+#    #+#             */
/*   Updated: 2016/12/24 23:42:19 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // REMOVE LATER!!!
#include "fdf.h"

// a = 0; w = 13; s = 1; d= 2; q = 12; e = 14
int			direction_detective(int key_press)
{
	if (key_press == 13 || key_press == 1 || key_press == 0 || key_press == 2 ||
		key_press == 12 || key_press == 14 || key_press == 6 ||
		key_press == 7 || key_press == 18 || key_press == 19 ||
		key_press == 8)
		return (1);
	else
		return (0);
}

// rotation = https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/3drota.htm
int			input_detective(int key_press, t_super *super_struct)
{
	printf("\n");
	printf("key_press = %d\n", key_press);
	mlx_clear_window(super_struct->mlx, super_struct->window);
	if (direction_detective(key_press))
	{
		// mlx_clear_window(super_struct->mlx, super_struct->window);
		if (key_press == 18 || key_press == 19)
			zoom_detective(super_struct, key_press);
		else
		{
			apply_angle(super_struct, key_press);
			z_axis(super_struct);
			y_axis(super_struct);
			x_axis(super_struct);
			// printf("BEFORE = min_x = %f, max_x = %f, min_y = %f, max_y = %f\n", super_struct->min_x, super_struct->max_x, super_struct->min_y, super_struct->max_y);
			printf("min_x = %f, max_x = %f, min_y = %f, max_y = %f\n", super_struct->min_x, super_struct->max_x, super_struct->min_y, super_struct->max_y);
			center_points(super_struct);
		}
		connect_lines(*super_struct);
	}
	else if (key_press == 3)
	{
		// mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("reset!\n");
		reset_points(super_struct);
	}
	else if (key_press == 53)
		exit(1);
	else
		printf("Error: not a valid keypress!\n");
	return (0);
}