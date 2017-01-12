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
# define X_ROT 5.0
# define Y_ROT 5.0
# define Z_ROT 5.0
# define WINDOW_X 1000.0
# define WINDOW_Y 1000.0
# define RES 0.1
# define SCALE 0.6
# define RADS(x) (x * M_PI / 180)

typedef struct	s_pt
{
	double			x;
	double			y;
	double			z;
	double			scaled_x;
	double			scaled_y;
	double			scaled_z;
	double			og_x;
	double			og_y;
	double			og_z;
}				t_pt;

typedef struct s_super
{		
	char			*file_name;
	t_pt			**map;
	char			**file_storage;
	int				rows;
	int				cols;
	void			*mlx;
	void			*window;
	double			window_x;
	double			window_y;
	double			max_z;
	double			min_z;
	double			step_unit;
	char			long_axis;
	double			start_x;
	double			start_y;
	double			angle_x;
	double			angle_y;
	double			angle_z;
	double			min_x;
	double			max_x;
	double			min_y;
	double			max_y;
	int				file_error;
	int				color;
	double			slope;
	double			y_int;
	double			x1;
	double			x2;
	double			y1;
	double			y2;
	double			z_delta;
	void			*img;		
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	unsigned int	*mem_addr;
}				t_super;

/* *********************** */
/*       rotation.c        */
/* *********************** */

void				x_axis(t_super *super_struct);
void				y_axis(t_super *super_struct);
void				z_axis(t_super *super_struct);

/* *********************** */
/*          draw.c         */
/* *********************** */

void				low_slope(t_super *super_struct);
void				high_slope(t_super *super_struct);
void				draw_line(int i, int j, t_super *super_struct, char letter);
void				connect_lines(t_super *super_struct);

/* *********************** */
/*     draw_support.c      */
/* *********************** */

void				init_draw_vars(int i, int j, t_super *super_struct, char letter);
void				image_prep(t_super *super_struct);

/* *********************** */
/*   superstruct_setup.c   */
/* *********************** */

void				assign_to_map(t_super *super_struct, t_pt *map, double x, double y);
void				init_superstruct(char *av1, t_super *super_struct);
void				scale_that_shit(t_super *super_struct);
void				scale_init_map(t_super *super_struct);
void				init_values(t_super *super_struct, char **av1);

/* *********************** */
/*     file_handling.c     */
/* *********************** */

void				find_num_cols(t_super *super_struct);
int					find_num_rows(char *file_name);
void	 			file_detective(t_super *super_struct);
void				parse_file(t_super *super_struct);
t_pt				*fill_map(char *r_char, t_pt *r_map, int map_row, int cols);

/* *********************** */
/*  debugging_functions.c  */
/* *********************** */

void				print_shit(t_super super_struct);
void				print_map(t_super *super_struct);
void				print_2D_chararray(char **array, int rows);

/* *********************** */
/*       key_press.c       */
/* *********************** */		

int					input_detective(int key_press, t_super *super_struct);
int					key_detective(int key_press);
void				quitting(t_super *super_struct);

/* *********************** */
/*    angle_wrangler.c     */
/* *********************** */

void				apply_angle(t_super *super_struct, int key_press);
void				ninty_rotation(t_super *super_struct, int key_press);

/* *********************** */
/*    error_checking.c     */
/* *********************** */

void				compare_cols(t_super *super_struct, int cols, int i);

/* *********************** */
/*    zoom_zoom_zoom.c     */
/* *********************** */

void				zoom_detective(t_super *super_struct, int key_press);
void				zooms(t_super *super_struct, double zoom_factor);

/* *********************** */
/*      adjustments.c      */
/* *********************** */

void				subtract_min_points(t_super *super_struct);
void				center_points(t_super *super_struct);
void				reset_points(t_super *super_struct);

/* *********************** */
/*     min_max_stuff.c     */
/* *********************** */

void				max_min_z(t_super *super_struct);
void				check_min_max(t_super *super_struct, int i, int j);
void				max_min_xy(t_super *super_struct);
void				init_min_max(t_super *super_struct);

#endif