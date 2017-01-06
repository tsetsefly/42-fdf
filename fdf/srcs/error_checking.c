/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_checking.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:56:50 by dtse              #+#    #+#             */
/*   Updated: 2016/12/15 16:56:57 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // REMOVE LATER!!!

void		compare_cols(t_super *super_struct, int cols, int i)
{
	if (i == 0)
		super_struct->cols = cols;
	else
	{
		if (super_struct->cols != cols)
			super_struct->file_error = 1;
	}
}
