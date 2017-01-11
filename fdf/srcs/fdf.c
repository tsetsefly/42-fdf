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

void		process_fdf(char *av1)
{
	t_super	super_struct;

	super_struct = init_superstruct(av1);
	if (super_struct.file_error)
		// need to handle file errors
		printf("Error: file format!\n");
	else
		connect_lines(super_struct);
	// test_print_spiral(super_struct.mlx, super_struct.window);  // REMOVE LATER!!!

}

int			main (int ac, char **av)
{
	if (ac == 2)
		process_fdf(av[1]);
	else
		printf("Error: didn't pass a file!\n"); // switch to ft_putstr
	return (0);
}