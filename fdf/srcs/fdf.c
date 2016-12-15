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

void		ft_swap_doubles(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// need to make this fit norm
void		draw_line(double x1, double y1, double x2, double y2, void *mlx, void *window, int color)
{
	double	i;
	double	slope;
	double	y_int;
	double	max;
	double	res;
	int		neg;

	slope = (y2 - y1) / (x2 - x1);
	y_int = y1 - slope * x1;
	// printf("START: slope = %f,\ty-int = %f,\tx-int = %f,\tx2 - x1 = %f\n", slope, y_int, x_int, x2 - x1);
	i = 0;
	res = (0.5);
	if (fabs(slope) < 1)
	{
		max = fabs(x2 - x1);
		neg = (x2 < x1) ? -1 : 1;
		while (i <= max)
		{
			mlx_pixel_put(mlx, window, x1, y1, color);
			// printf("PIXEL: x = %f, y = %f, i = %f\n", x1, y1, i);
			x1 += (res * neg);
			y1 = slope * x1 + y_int;
			i += res;
		}
	}
	else
	{
		max = fabs(y2 - y1);
		neg = (y2 < y1) ? -1 : 1;
		while (i <= max)
		{
			mlx_pixel_put(mlx, window, x1, y1, color);
			// printf("PIXEL: x = %f, y = %f, i = %f\n", x1, y1, i);
			y1 += (res * neg);
			x1 = (x1 == x2) ? x2 : ((y1 - y_int) / slope);
			i += res;
		}
	}	
}

// rotation = https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/3drota.htm
int		input_detective(int key_press, /*void *mlx, */t_super *super_struct)
{
	printf("key_press = %d\n", key_press);
	if (key_press == 126)
		printf("up!\n");
		// printf("%f\n", super_struct.map[2][2]->scaled_z);
	if (key_press == 53)
		exit(1);
	(void)super_struct;
	return (0);
}

void		print_2D_chararray(char **array, int rows)
{
	int		i;
	size_t	len;
	
	i = 0;
	len = 0;
	ft_putstr("wahoo!\n");
	while (i < rows)
	{
		ft_putstr(array[i]);
		ft_putchar('\n');
		i++;
	}
}

int		find_num_cols(char *array)
{
	int i;
	int len;
	int cols;

	len = ft_strlen(array);
	i = 0;
	cols = 0;
	while (i < len)
	{
		if (array[i] == ' ')
		{
			cols++;
			while (array[i] == ' ')
				i++;
		}
		else
			i++;
	}
	cols++;
	return (cols);
}

t_pt		*fill_map(char *r_char, t_pt *r_map, int map_row, int cols)
{
	int		i;
	char	**num_char_array;

	num_char_array = ft_strsplit(r_char, ' '); // may need to come back later to error check for other delimiters

	// need to add in the HEX color parsing here
	i = 0;
	while (i < cols)
	{
		r_map[i].og_x = map_row;
		r_map[i].og_y = i;
		r_map[i].og_z = ft_atoi(num_char_array[i]);
		i++;
	}
	return (r_map);
}

void		print_map(t_super super_struct)
{
	int i;
	int j;

	i = 0;
	while (i < super_struct.rows)
	{
		j = 0;
		while (j < super_struct.cols)
		{
			printf("(%d,%d) %d \t", (int)super_struct.map[i][j].og_x, (int)super_struct.map[i][j].og_y, (int)super_struct.map[i][j].og_z);
			j++;
		}
		printf("\n");
		i++;
	}
}

// can probably merge this in later to something like the scaling
t_super		max_min_z(t_super super_struct)
{
	int		i;
	int		j;

	i = 0;
	super_struct.max_z = super_struct.map[0][0].og_z;
	super_struct.min_z = super_struct.map[0][0].og_z;
	printf("MAX_Z = %f, MIN_Z = %f\n", super_struct.max_z, super_struct.min_z);
	while (i < super_struct.rows)
	{
		j = 0;
		while (j < super_struct.cols)
		{
			// printf("(%d, %d) %f\t", i, j, super_struct.map[i][j].og_z);
			if (super_struct.map[i][j].og_z > super_struct.max_z)
			{
				super_struct.max_z = super_struct.map[i][j].og_z;
				// printf("MAX_Z = %f, MIN_Z = %f\n", super_struct.max_z, super_struct.min_z);
			}
			else if (super_struct.map[i][j].og_z < super_struct.min_z)
			{
				super_struct.min_z = super_struct.map[i][j].og_z;
				// printf("MAX_Z = %f, MIN_Z = %f\n", super_struct.max_z, super_struct.min_z);
			}
			j++;
		}
		i++;
	}
	printf("MAX_Z = %f, MIN_Z = %f\n", super_struct.max_z, super_struct.min_z);
	return (super_struct);
}

t_super		parse_file(t_super super_struct)
{
	int		i;

	super_struct.cols = find_num_cols(super_struct.file_storage[0]);
	printf("ROWS = %d, COLS = %d\n", super_struct.rows, super_struct.cols);
	super_struct.map = (t_pt **)malloc(sizeof(t_pt *) * super_struct.rows);
	i = 0;
	while (i < super_struct.rows)
		super_struct.map[i++] = (t_pt *)malloc(sizeof(t_pt) * super_struct.cols);
	i = 0;
	while (i < super_struct.rows)
	{
		super_struct.map[i] = fill_map(super_struct.file_storage[i], super_struct.map[i], i, super_struct.cols);
		i++;
	}
	print_map(super_struct);
	return (super_struct = max_min_z(super_struct));
}

int			find_num_rows(char *file_name)
{
	int		fd;
	char	*line;
	int		rows;

	fd = open(file_name, O_RDONLY);
	rows = 0;
	while (get_next_line(fd, &line) > 0)
	{
		printf("%s\n", line);
		rows++;
		free(line);
  	}
  	// printf("ROWS = %d\n", rows);
	close(fd);
	return (rows);
}

t_super 	file_detective(t_super super_struct)
{
	int		fd;
	size_t	len;
	char	*line;

	super_struct.rows = find_num_rows(super_struct.file_name);
	super_struct.file_storage = (char **)malloc(sizeof(char *) * (super_struct.rows + 1));
	fd = open(super_struct.file_name, O_RDONLY);
	super_struct.rows = 0;
	len = 0;
  	while (get_next_line(fd, &line) > 0)
	{
		len = ft_strlen(line);
		// printf("%s\tLEN = %lu\n", line, len);
		super_struct.file_storage[super_struct.rows] = (char *)malloc(sizeof(char) * (len + 1));
		ft_strcpy(super_struct.file_storage[super_struct.rows], line);
		super_struct.rows++;
		free(line);
  	}
  	super_struct.file_storage[super_struct.rows] = 0;
  	print_2D_chararray(super_struct.file_storage, super_struct.rows);
  	return(super_struct = parse_file(super_struct));
}

// void		test_print_spiral(void *mlx, void *window) // REMOVE LATER!!!
// {
// 	int		color = 140 * 65536; // RGB = (R*65536)+(G*256)+B , (when R is RED, G is GREEN and B is BLUE)
// 	int 	color_change = 8;

// 	// VERTICAL LINE UP --> DOWN HERE
// 	draw_line(400, 200, 400, 400, mlx, window, color += color_change);

// 	draw_line(450, 200, 400, 400, mlx, window, color += color_change);
// 	draw_line(500, 200, 400, 400, mlx, window, color += color_change);
// 	draw_line(550, 200, 400, 400, mlx, window, color += color_change);
	
// 	draw_line(600, 200, 400, 400, mlx, window, color += color_change);
	
// 	draw_line(600, 250, 400, 400, mlx, window, color += color_change);
// 	draw_line(600, 300, 400, 400, mlx, window, color += color_change);
// 	draw_line(600, 350, 400, 400, mlx, window, color += color_change);
	
// 	draw_line(600, 400, 400, 400, mlx, window, color += color_change);
	
// 	draw_line(600, 450, 400, 400, mlx, window, color += color_change);
// 	draw_line(600, 500, 400, 400, mlx, window, color += color_change);
// 	draw_line(600, 550, 400, 400, mlx, window, color += color_change);
	
// 	draw_line(600, 600, 400, 400, mlx, window, color += color_change);

// 	draw_line(550, 600, 400, 400, mlx, window, color += color_change);
// 	draw_line(500, 600, 400, 400, mlx, window, color += color_change);
// 	draw_line(450, 600, 400, 400, mlx, window, color += color_change);

// 	// VERTICAL LINE DOWN --> UP HERE
// 	draw_line(400, 600, 400, 400, mlx, window, color += color_change);

// 	draw_line(350, 600, 400, 400, mlx, window, color += color_change);
// 	draw_line(300, 600, 400, 400, mlx, window, color += color_change);
// 	draw_line(250, 600, 400, 400, mlx, window, color += color_change);

// 	draw_line(200, 600, 400, 400, mlx, window, color += color_change);

// 	draw_line(200, 550, 400, 400, mlx, window, color += color_change);
// 	draw_line(200, 500, 400, 400, mlx, window, color += color_change);
// 	draw_line(200, 450, 400, 400, mlx, window, color += color_change);

// 	draw_line(200, 400, 400, 400, mlx, window, color += color_change);

// 	draw_line(200, 350, 400, 400, mlx, window, color += color_change);
// 	draw_line(200, 300, 400, 400, mlx, window, color += color_change);
// 	draw_line(200, 250, 400, 400, mlx, window, color += color_change);

// 	draw_line(200, 200, 400, 400, mlx, window, color += color_change);

// 	draw_line(250, 200, 400, 400, mlx, window, color += color_change);
// 	draw_line(300, 200, 400, 400, mlx, window, color += color_change);
// 	draw_line(350, 200, 400, 400, mlx, window, color += color_change);

// 	mlx_key_hook(window, (void *)input_detective, mlx);
// 	mlx_loop(mlx);
// }

void		print_shit(t_super super_struct)
{
	int		i;
	int		j;
	int		color = 140 * 65536;

	i = 0;
	while (i < super_struct.rows)
	{
		j = 0;
		while (j < super_struct.cols)
		{
			mlx_pixel_put(super_struct.mlx, super_struct.window, super_struct.map[i][j].scaled_x, super_struct.map[i][j].scaled_y, color);
			j++;
		}
		i++;
	}
	mlx_key_hook(super_struct.window, input_detective, &super_struct);
	mlx_loop(super_struct.mlx);
}

t_super		scale_init_map(t_super super_struct)
{
	int		i;
	int		j;
	double	x;
	double	y;

	y = super_struct.start_y;
	i = 0;
	while (i < super_struct.rows)
	{
		j = 0;
		x = super_struct.start_x;
		while (j < super_struct.cols)
		{
			super_struct.map[i][j].scaled_x = x;
			super_struct.map[i][j].scaled_y = y;
			super_struct.map[i][j].scaled_z = super_struct.map[i][j].og_z * super_struct.step_unit;
			super_struct.map[i][j].x = x;
			super_struct.map[i][j].y = y;
			super_struct.map[i][j].z = super_struct.map[i][j].scaled_z;
			x += super_struct.step_unit;
			j++;
		}
		y += super_struct.step_unit;
		i++;
	}
	return (super_struct);
}

t_super		scale_that_shit(t_super super_struct)
{
	super_struct.step_unit = 0;

	// not quite centered
	if (super_struct.cols >= super_struct.rows)
	{
		super_struct.step_unit = ((3 * super_struct.window_x) / 5) / (super_struct.cols + 1);
		super_struct.long_axis = 'x';
	}
	else
	{
		super_struct.step_unit = ((3 * super_struct.window_y) / 5) / (super_struct.rows + 1);
		super_struct.long_axis = 'y';
	}
	super_struct.start_x = (super_struct.window_x / 2) - (super_struct.step_unit * (super_struct.cols) / 2);
	super_struct.start_y = (super_struct.window_y / 2) - (super_struct.step_unit * (super_struct.rows) / 2);
	printf("step unit = %f, axis = %c, start_x = %f, start_y = %f\n", super_struct.step_unit, super_struct.long_axis, super_struct.start_x, super_struct.start_y);
	super_struct = scale_init_map(super_struct);
	// print_shit(super_struct);
	return (super_struct);
}

// void		draw_line(double x1, double y1, double x2, double y2, void *mlx, void *window, int color)
void		connect_lines(t_super super_struct)
{
	int		i;
	int		j;
	int		color = 140 * 65536;

	i = 0;
	while (i < super_struct.rows)
	{
		j = 0;
		while (j < super_struct.cols)
		{
			if (j < super_struct.cols - 1)
				draw_line(super_struct.map[i][j].x, super_struct.map[i][j].y, super_struct.map[i][j + 1].x, super_struct.map[i][j + 1].y, super_struct.mlx, super_struct.window, color);
			if (i < super_struct.rows - 1)
				draw_line(super_struct.map[i][j].x, super_struct.map[i][j].y, super_struct.map[i + 1][j].x, super_struct.map[i + 1][j].y, super_struct.mlx, super_struct.window, color);
			j++;
		}
		i++;
	}
	mlx_key_hook(super_struct.window, input_detective, &super_struct);
	mlx_loop(super_struct.mlx);
}

t_super		init_superstruct(char *av1)
{
	t_super	super_struct;

	// can make this more efficient with pointers instead of copying variables through functions
	super_struct.window_x = 1000;
	super_struct.window_y = 1000;
	super_struct.angle_x = 0;
	super_struct.angle_y = 0;
	super_struct.angle_z = 0;
	super_struct.file_name = av1;
	super_struct = file_detective(super_struct);
	super_struct.mlx = mlx_init();
	super_struct.window = mlx_new_window(super_struct.mlx, super_struct.window_x, super_struct.window_y, "detective");
	super_struct = scale_that_shit(super_struct);
	return (super_struct);
}

int			main (int ac, char **av)
{
	t_super	super_struct;
	
	if (ac == 2)
	{
		super_struct = init_superstruct(av[1]);
		connect_lines(super_struct);
		// test_print_spiral(super_struct.mlx, super_struct.window);  // REMOVE LATER!!!
	}
	else
		printf("Error: didn't pass a file!\n");
	return (0);
}