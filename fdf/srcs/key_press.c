/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
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
		key_press == 12 || key_press == 14)
		return (1);
	else
		return (0);
}

// rotation = https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/3drota.htm

// should re-center after each rotation
int			input_detective(int key_press, t_super *super_struct)
{
	printf("key_press = %d\n", key_press);
	// 'W' = x
	if (key_press == 13)
	{
		mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("x!\n");
		x_axis(super_struct, 1);
	}
	// 'S' = -x
	else if (key_press == 1)
	{
		mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("-x!\n");
		x_axis(super_struct, -1);
	}
	// 'A' = y
	else if (key_press == 0)
	{
		mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("y!\n");
		y_axis(super_struct, 1);
	}
	// 'D' = -y
	else if (key_press == 2)
	{
		mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("-y!\n");
		y_axis(super_struct, -1);
	}
	// 'Q' = z
	else if (key_press == 12)
	{
		mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("z!\n");
		// printf("%f\n", super_struct->map[2][2].scaled_z);
		z_axis(super_struct, 1);
	}
	// 'E' = -z
	else if (key_press == 14)
	{
		mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("-z!\n");
		z_axis(super_struct, -1);
	}
	// 'F' = reset
	else if (key_press == 3)
	{
		mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("reset!\n");
		reset_points(super_struct);
	}
	else if (key_press == 53)
		exit(1);
	else
		printf("Error: not a valid keypress!\n");
	// (void)super_struct; //
	return (0);
}