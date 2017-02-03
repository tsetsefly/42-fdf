# FDF

TL;DR = "This project is about creating a simplified 3D graphic representation of a relief landscape."
* FDF stands for "fils de fer," or _wireframe_ in French

## Methods of rotation

[Siggraph article](https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/3drota.htm)
* Order matters
* Need temporary variables for changes to prime values within transformations within axis rotations

## MinilibX

C graphics library used to open windows, light pixels, deal with events.
* [Man pages](https://github.com/tsetsefly/42-fdf/tree/master/minilibx_macos/man)

## Error checking
### One file
```c
// fdf.c --> main
int	main(int ac, char **av)
{
	if (ac == 2)
		process_fdf(av[1]);
	else
		ft_putstr("Error: incorrect number of files!\n");
```
### File errors
Checks for errors with file reading
```c
// file_handling.c --> file_detective
if ((fd = open(super_struct->file_name, O_RDONLY)) < 0)
{
    super_struct->file_error = 1;
    return ;
}
```
Checks for consistent number of columns
```c
// error_checking.c --> compare_cols
if (i == 0)
	super_struct->cols = cols;
else
{
	if (super_struct->cols != cols)
		super_struct->file_error = 1;
}
```
Check for errors caught after file handling and struct setup
```c
// fdf.c --> main
if (super_struct->file_error)
    ft_putstr("Error: file error!\n");
```
## File handling
### File storage
Initial file is copied to the structure as an array of strings. Allows for additional parsing later as needed (didn't implement HEX color parsing but could deal with it from this array).
```c
// file_handling.c --> file_detective
// malloc'ing array
super_struct->file_storage = (char **)malloc(sizeof(char *) * (super_struct->rows + 1));
// later in a loop: copying lines in file to struct
super_struct->file_storage[super_struct->rows] = (char *)malloc(sizeof(char) * (len + 1));
ft_strcpy(super_struct->file_storage[super_struct->rows], line);
```
### Parsing string to initialize map of coordinates
Creating the map
```c
// file_handling.c --> parse_file
// malloc'ing for each row in the array of map points
super_struct->map = (t_pt **)malloc(sizeof(t_pt *) * (super_struct->rows));
// later in a loop: malloc'ing for columns in the array of map points
super_struct->map[i] = (t_pt *)malloc(sizeof(t_pt) * (super_struct->cols));
```
Assigning original values to the map
```c
// file_handling.c --> parse_file
// inside the same loop as above
super_struct->map[i] = fill_map(super_struct->file_storage[i], super_struct->map[i], i, super_struct->cols);
// file_handling.c --> fill_map
// in the function fill_map: assigning starting x, y, z coordinates as og_x, og_y, og_z
num_char_array = ft_strsplit(r_char, ' ');
i = 0;
while (i < cols)
{
    r_map[i].og_x = map_row;
    r_map[i].og_y = i;
    r_map[i].og_z = ft_atoi(num_char_array[i]);
    i++;
}
```
Determining the appropriate scale factor for the window
```c
// superstruct_setup.c --> scale_that_shit
// determines which is the longest axis and scales accordingly
if (super_struct->cols >= super_struct->rows && super_struct->cols
	>= super_struct->z_delta)
{
	super_struct->step_unit = WINDOW_X * SCALE
		/ (super_struct->cols - 1);
	super_struct->long_axis = 'x';
}
else if (super_struct->rows >= super_struct->cols && super_struct->rows
	>= super_struct->z_delta)
{
	super_struct->step_unit = WINDOW_Y * SCALE
		/ (super_struct->rows - 1);
	super_struct->long_axis = 'y';
}
else
{
	super_struct->step_unit = ((WINDOW_X + WINDOW_Y) / 2)
		/ super_struct->z_delta;
	super_struct->long_axis = 'z';
}
```
Assigning scaled values to the map
```c
// superstruct_setup.c --> scale_init_map
// looping through the rows, columns
y = 0;
i = 0;
while (i < super_struct->rows)
{
	j = 0;
	x = 0;
	while (j < super_struct->cols)
	{
		assign_to_map(super_struct, &super_struct->map[i][j], x, y);
		x += super_struct->step_unit;
		j++;
	}
	y += super_struct->step_unit;
	i++;
}
// superstruct_setup.c --> assign_to_map
map->scaled_x = x;
map->scaled_y = y;
map->scaled_z = map->og_z * super_struct->step_unit / 2;
map->x = x;
map->y = y;
map->z = map->scaled_z;
```
## Drawing
Looping through map, point-by-point
```c
// draw.c --> connect_lines
while (i < super_struct->rows)
{
	j = 0;
	while (j < super_struct->cols)
	{
		if (j < super_struct->cols - 1)
			draw_line(i, j, super_struct, 'j');
		if (i < super_struct->rows - 1)
			draw_line(i, j, super_struct, 'i');
		j++;
	}
	i++;
}
```
Low slopes (less than 1)
```c
// draw.c --> low_slope
max = fabs(super_struct->x2 - super_struct->x1);
neg = (super_struct->x2 < super_struct->x1) ? -1 : 1;
while (k <= max)
{
	super_struct->mem_addr[(int)(round(super_struct->y1)
		* round(super_struct->max_x + 1) + round(super_struct->x1))]
		= super_struct->color;
	super_struct->x1 += (RES * neg);
	super_struct->y1 = super_struct->slope * super_struct->x1
		+ super_struct->y_int;
	k += RES;
}
```
High slopes (greater than or equal to 1)
```c
// draw.c --> high_slope
max = fabs(super_struct->y2 - super_struct->y1);
neg = (super_struct->y2 < super_struct->y1) ? -1 : 1;
while (k <= max)
{
	super_struct->mem_addr[(int)(round(super_struct->y1)
		* round(super_struct->max_x + 1) + round(super_struct->x1))]
		= super_struct->color;
	super_struct->y1 += (RES * neg);
	super_struct->x1 = (super_struct->x1 == super_struct->x2) ?
		super_struct->x2 : ((super_struct->y1 - super_struct->y_int)
		/ super_struct->slope);
	k += RES;
}
```
Drawing lines
```c
// draw.c --> draw_line
if (fabs(super_struct->slope) < 1)
	low_slope(super_struct);
else
	high_slope(super_struct);
```
Connecting lines
```c
// draw.c --> connect_lines
while (i < super_struct->rows)
{
	j = 0;
	while (j < super_struct->cols)
	{
		if (j < super_struct->cols - 1)
			draw_line(i, j, super_struct, 'j');
		if (i < super_struct->rows - 1)
			draw_line(i, j, super_struct, 'i');
		j++;
	}
	i++;
}
```
Working with the graphics library (MinilibX)
```c
// draw.c --> connect_lines
// taking image and placing it in middle
mlx_put_image_to_window(super_struct->mlx, super_struct->window,
	super_struct->img, round((WINDOW_X - super_struct->max_x) / 2),
	round((WINDOW_Y - super_struct->max_y) / 2));
// listening for key-presses
mlx_key_hook(super_struct->window, input_detective, super_struct);
mlx_loop(super_struct->mlx);
```
## Input detection
### Rotation key presses
|Axis    |(+) radians|(-) radians|(+) 90-degrees|
|:------:|:---------:|:---------:|:------------:|
|X-AXIS  |S          |W          |X             |
|X-AXIS  |A          |D          |C             |
|Z-AXIS  |Q          |E          |Z             |
### Other key presses
-Zoom-in = *1*
-Zoom-out = *2*
-Reset back to initial map = *F*
### Applying angle of rotation
```c
// angle_wrangler.c --> apply_angle
if (key_press == 0 || key_press == 2)
{
	if (key_press == 2)
		super_struct->angle_y += Y_ROT;
	else
		super_struct->angle_y -= Y_ROT;
}
else if (key_press == 13 || key_press == 1)
{
...
```
Changing the coordinates based on angle changes based on this [Siggraph article] (https://www.siggraph.org/education/materials/HyperGraph/modeling/mod_tran/3drota.htm)
```c
// rotation.c --> x_axis
super_struct->map[i][j].x = super_struct->map[i][j].scaled_x;
super_struct->map[i][j].y =
	super_struct->map[i][j].scaled_y * cos(RADS(super_struct->angle_x))
	- super_struct->map[i][j].scaled_z * sin(RADS(super_struct->angle_x));
super_struct->map[i][j].z =
	super_struct->map[i][j].scaled_y * sin(RADS(super_struct->angle_x))
	+ super_struct->map[i][j].scaled_z * cos(RADS(super_struct->angle_x));
```
