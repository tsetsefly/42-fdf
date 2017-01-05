/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle_wrangler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 00:08:15 by dtse              #+#    #+#             */
/*   Updated: 2016/12/25 00:08:16 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // REMOVE LATER!!!
#include "fdf.h"

// a = 0; w = 13; s = 1; d= 2; q = 12; e = 14
// x_axis(super_struct, 1);
// x_axis(super_struct, -1);
// y_axis(super_struct, 1);
// y_axis(super_struct, -1);
// z_axis(super_struct, 1);
// z_axis(super_struct, -1);
void		apply_angle(t_super *super_struct, int key_press)
{
	if (key_press == 0 || key_press == 2)
	{
		if (key_press == 2)
			super_struct->angle_y += (Y_ROT * M_PI / 180.0);
		else
			super_struct->angle_y += (Y_ROT * M_PI / 180.0) * -1;
	}
	else if (key_press == 13 || key_press == 1)
	{
		if (key_press == 13)
			super_struct->angle_x += (X_ROT * M_PI / 180.0);
		else
			super_struct->angle_x += (X_ROT * M_PI / 180.0) * -1;
	}
	else if (key_press == 12 || key_press == 14)
	{
		if (key_press == 12)
			super_struct->angle_z += (Z_ROT * M_PI / 180.0);
		else
			super_struct->angle_z += (Z_ROT * M_PI / 180.0) * -1;
	}
	else if (key_press == 6 || key_press == 7 || key_press == 8)
		ninty_rotation(super_struct, key_press);
}

void		ninty_rotation(t_super *super_struct, int key_press)
{
	if (key_press == 6)
		super_struct->angle_z += (90 * M_PI / 180.0);
	else if (key_press == 7)
		super_struct->angle_x += (90 * M_PI / 180.0);
}

// need to update the angle based on key press
// need to apply the axis equation to each point in the map
// radians = degrees * pi / 180
// need to translate from neutral position each time? in that case need to sequentially run against x, y, z
	// super_struct->angle_x += (X_ROT * M_PI / 180.0) * neg;
	// printf("angle_x = %f, angle_y = %f, angle_z = %f\n", super_struct->angle_x, super_struct->angle_y, super_struct->angle_z);

	// super_struct->angle_y += (Y_ROT * M_PI / 180.0) * neg;
	// printf("angle_x = %f, angle_y = %f, angle_z = %f\n", super_struct->angle_x, super_struct->angle_y, super_struct->angle_z);

	// super_struct->angle_z += (Z_ROT * M_PI / 180.0) * neg;
	// printf("angle_x = %f, angle_y = %f, angle_z = %f\n", super_struct->angle_x, super_struct->angle_y, super_struct->angle_z);