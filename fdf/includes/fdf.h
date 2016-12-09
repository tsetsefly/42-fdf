/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 17:47:05 by dtse              #+#    #+#             */
/*   Updated: 2016/11/15 17:47:07 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../minilibx_macos/mlx.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>

typedef struct	s_pt
{
	double	x;
	double	y;
	double	z;
	double	scaled_x;
	double	scaled_y;
	double	scaled_z;
	double	og_x;
	double	og_y;
	double	og_z;
}				t_pt;

typedef struct s_super
{
	char	*file_name;
	t_pt	**map;
	char	**file_storage;
	int		rows;
	int		cols;
	void	*mlx;
	void	*window;
	int		window_x;
	int		window_y;
}				t_super;

#endif