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
#include <stdio.h> // REMOVE LATER!!!! //

int			main (int ac, char **av)
{
	t_super	super_struct;
	
	if (ac == 2)
	{
		super_struct = init_superstruct(av[1]);
		if (super_struct.file_error)
			printf("Error: file format!\n");
		else
			connect_lines(super_struct);
		// test_print_spiral(super_struct.mlx, super_struct.window);  // REMOVE LATER!!!
	}
	else
		printf("Error: didn't pass a file!\n");
	return (0);
}