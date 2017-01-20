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

#include "fdf.h"
#include <stdio.h> // REMOVE LATER!!!

/* *********************************** */
/* Y-AXIS: 'a' = 0;  'd' = 2;  'c' = 8 */
/* X-AXIS: 'w' = 13; 's' = 1;  'x' = 7 */
/* Z-AXIS: 'q' = 12; 'e' = 14; 'z' = 6 */
/* *********************************** */

void		apply_angle(t_super *super_struct, int key_press)
{
	if (key_press == 0 || key_press == 2)
	{
		if (key_press == 2)
			super_struct->angle_y += Y_ROT;
		else
			super_struct->angle_y -= Y_ROT;
	}
	else if (key_press == 13 || key_press == 1)
	{
		if (key_press == 13)
			super_struct->angle_x += X_ROT;
		else
			super_struct->angle_x -= X_ROT;
	}
	else if (key_press == 12 || key_press == 14)
	{
		if (key_press == 12)
			super_struct->angle_z += Z_ROT;
		else
			super_struct->angle_z -= Z_ROT;
	}
	else if (key_press == 6 || key_press == 7 || key_press == 8)
		ninty_rotation(super_struct, key_press);
	// printf("X_ROT = %f, Y_ROT = %f, Z_ROT = %f\n", X_ROT, Y_ROT, Z_ROT);
	// printf("angle_x = %f, angle_y = %f, angle_z = %f\n", super_struct->angle_x, super_struct->angle_y, super_struct->angle_z); // REMOVE LATER!!!
}

void		ninty_rotation(t_super *super_struct, int key_press)
{
	if (key_press == 6)
		super_struct->angle_z += 90;
	else if (key_press == 7)
		super_struct->angle_x += 90;
	else if (key_press == 8)
		super_struct->angle_y += 90;
}
