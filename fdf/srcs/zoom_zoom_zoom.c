/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom_zoom_zoom.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 17:15:35 by dtse              #+#    #+#             */
/*   Updated: 2016/12/15 17:15:37 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // REMOVE LATER!!!! //

void		zoom_detective(t_super *super_struct, int key_press)
{
	if (key_press == 18)
		zooms(super_struct, 0.90);
	else
		zooms(super_struct, 1.10);
}

void		zooms(t_super *super_struct, double zoom_factor)
{
	int		i;
	int		j;

	i = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		while (j < super_struct->cols)
		{
			super_struct->map[i][j].z = super_struct->map[i][j].z * zoom_factor;
			super_struct->map[i][j].x = super_struct->map[i][j].x * zoom_factor;
			super_struct->map[i][j].y = super_struct->map[i][j].y * zoom_factor;
			j++;
		}
		i++;
	}
}
