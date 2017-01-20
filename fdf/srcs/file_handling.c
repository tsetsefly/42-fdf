/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtse <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 16:56:50 by dtse              #+#    #+#             */
/*   Updated: 2016/12/15 16:56:57 by dtse             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h> // REMOVE LATER!!!

void		find_num_cols(t_super *super_struct)
{
	int		i;
	int		j;
	int		len;
	int		cols;

	i = 0;
	while (i < super_struct->rows)
	{
		j = 0;
		cols = 0;
		len = ft_strlen(super_struct->file_storage[i]);
		while (j < len)
		{
			if (super_struct->file_storage[i][j] != ' ')
			{
				cols++;
				while (super_struct->file_storage[i][j] != ' ')
					j++;
			}
			else
				j++;
		}
		compare_cols(super_struct, cols, i);
		i++;
	}
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
		// printf("%s\n", line);
		rows++;
		free(line);
  	}
  	// printf("ROWS = %d\n", rows);
	close(fd);
	return (rows);
}

t_pt		*fill_map(char *r_char, t_pt *r_map, int map_row, int cols)
{
	int		i;
	char	**num_char_array;

	num_char_array = ft_strsplit(r_char, ' ');

	// need to add in the HEX color parsing here
	// need to add checking for non-number characters here
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

void		parse_file(t_super *super_struct)
{
	int		i;

	find_num_cols(super_struct);
	if (super_struct->file_error)
		return ;
	// printf("ROWS = %d, COLS = %d\n", super_struct->rows, super_struct->cols);
	super_struct->map = (t_pt **)malloc(sizeof(t_pt *) * (super_struct->rows));
	i = 0;
	while (i < super_struct->rows)
	{
		super_struct->map[i] =
			(t_pt *)malloc(sizeof(t_pt) * (super_struct->cols));
		super_struct->map[i] =
			fill_map(super_struct->file_storage[i], super_struct->map[i], i,
				super_struct->cols);
		i++;
	}
	print_map(super_struct); // remove later!!!
	max_min_z(super_struct);
}

void 		file_detective(t_super *super_struct)
{
	int		fd;
	size_t	len;
	char	*line;

	super_struct->rows = find_num_rows(super_struct->file_name);
	super_struct->file_storage =
		(char **)malloc(sizeof(char *) * (super_struct->rows + 1));
	if ((fd = open(super_struct->file_name, O_RDONLY)) < 0)
	{
		super_struct->file_error = 1;
		return ;
	}
	super_struct->rows = 0;
	len = 0;
  	while (get_next_line(fd, &line) > 0) // stores a string of each line in super_struct->file_storage
	{
		len = ft_strlen(line);
		// printf("%s\tLEN = %lu\n", line, len);
		super_struct->file_storage[super_struct->rows] =
			(char *)malloc(sizeof(char) * (len + 1));
		ft_strcpy(super_struct->file_storage[super_struct->rows], line);
		super_struct->rows++;
		free(line);
  	}
  	super_struct->file_storage[super_struct->rows] = 0; // caps the line
  	print_2D_chararray(super_struct->file_storage, super_struct->rows); // remove later, just prints stuff... or can add this function to libft
  	parse_file(super_struct);
}
