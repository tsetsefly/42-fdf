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
	t_super	*super_struct;

	super_struct = (t_super *)malloc(sizeof(t_super));
	init_superstruct(av1, super_struct);
	if (super_struct->file_error)
		ft_putstr("Error: file error!\n");
	else
		connect_lines(super_struct);
	// test_print_spiral(super_struct.mlx, super_struct.window);  // REMOVE LATER!!!
}

int			main (int ac, char **av)
{
	if (ac == 2)
		process_fdf(av[1]);
	else
		ft_putstr("Error: incorrect number of files!\n");
	return (0);
}