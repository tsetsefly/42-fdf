/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 17:40:18 by dtse              #+#    #+#             */
/*   Updated: 2016/11/15 17:40:19 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // REMOVE LATER!!!!

// rotation = https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/3drota.htm
// a = 0; w = 13; s = 1; d= 2; q = 12; e = 14
int			input_detective(int key_press, t_super *super_struct)
{
	printf("key_press = %d\n", key_press);
	if (key_press == 13)
	{
		mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("x!\n");
		x_axis(super_struct, 1);
	}
	if (key_press == 1)
	{
		mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("-x!\n");
		x_axis(super_struct, -1);
	}
	else if (key_press == 0)
	{
		mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("y!\n");
		y_axis(super_struct, 1);
	}
	else if (key_press == 2)
	{
		mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("-y!\n");
		y_axis(super_struct, -1);
	}
	else if (key_press == 12)
	{
		mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("z!\n");
		// printf("%f\n", super_struct->map[2][2].scaled_z);
		z_axis(super_struct, 1);
	}
	else if (key_press == 14)
	{
		mlx_clear_window(super_struct->mlx, super_struct->window);
		printf("-z!\n");
		z_axis(super_struct, -1);
	}
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
	// (void)super_struct;
	return (0);
}

int			main (int ac, char **av)
{
	t_super	super_struct;
	
	if (ac == 2)
	{
		super_struct = init_superstruct(av[1]);
		connect_lines(super_struct);
		// test_print_spiral(super_struct.mlx, super_struct.window);  // REMOVE LATER!!!
	}
	else
		printf("Error: didn't pass a file!\n");
	return (0);
}