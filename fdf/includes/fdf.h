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
# define X_ROT 5
# define Y_ROT 5
# define Z_ROT 5
# define WINDOW_X 1000
# define WINDOW_Y 1000

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
	double	window_x; // why do I need these?
	double	window_y; // why do I need these?
	double	max_z;
	double	min_z;
	double	step_unit;
	char	long_axis;
	double	start_x;
	double	start_y;
	double	angle_x;
	double	angle_y;
	double	angle_z;
	double	min_x;
	double	max_x;
	double	min_y;
	double	max_y;
	int		file_error;
}				t_super;

// fdf.c
// int main(int ac, char **av);

// rotation.c
void		x_axis(t_super *super_struct);
void		y_axis(t_super *super_struct);
void		z_axis(t_super *super_struct);
void		center_points(t_super *super_struct);
void		reset_points(t_super *super_struct);

// draw.c
void		draw_line(double x1, double y1, double x2, double y2, void *mlx, void *window, int color);
void		connect_lines(t_super super_struct);

// superstruct_setup.c
t_super		init_superstruct(char *av1);
void		scale_that_shit(t_super *super_struct);
void		scale_init_map(t_super *super_struct);
void		init_values(t_super *super_struct, char **av1);
void		max_min_z(t_super *super_struct);

// file_handling.c
void		find_num_cols(t_super *super_struct);
int			find_num_rows(char *file_name);
void	 	file_detective(t_super *super_struct);
void		parse_file(t_super *super_struct);
t_pt		*fill_map(char *r_char, t_pt *r_map, int map_row, int cols);

// debugging_functions.c
void		print_shit(t_super super_struct);
void		print_map(t_super *super_struct);
void		print_2D_chararray(char **array, int rows);
// void		ft_swap_doubles(double *a, double *b);
// void		test_print_spiral(void *mlx, void *window);

// key_press.c
int			input_detective(int key_press, t_super *super_struct);
int			direction_detective(int key_press);

// angle_wrangler.c
void		apply_angle(t_super *super_struct, int key_press);
void		ninty_rotation(t_super *super_struct, int key_press);

// error_checking.c
void		compare_cols(t_super *super_struct, int cols, int i);

#endif