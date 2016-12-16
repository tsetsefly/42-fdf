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

// rotation = https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/3drota.htm //
int			input_detective(int key_press, t_super *super_struct)
{
	printf("key_press = %d\n", key_press);
	if (key_press == 126)
		printf("up!\n");
		printf("%f\n", super_struct->map[2][2].scaled_z);
		x_axis(super_struct);
	if (key_press == 53)
		exit(1);
	(void)super_struct;
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